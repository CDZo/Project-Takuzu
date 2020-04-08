#include "ModelTakuzu.h"
#include <iostream>
ModelTakuzu::ModelTakuzu(QObject *parent) : QObject(parent)
{

}

ModelTakuzu::~ModelTakuzu()
{
    delete [] _pawnGrid;
    _observers.clear();
}

void ModelTakuzu::setSize(const int &size)
{
    _gridSize = size;

}

void ModelTakuzu::initGrid(const int &size)
{
    _gridSize = size;
    _pawnGrid = new Pawn[size * size];
}

void ModelTakuzu::initGrid(const int &size, Pawn *pawns)
{
    _gridSize = size;
    _pawnGrid = new Pawn[size * size];
    for(int i = 0; i< size*size;i++ ) {
        _pawnGrid[i].setState(pawns[i].getState());
        _pawnGrid[i].setId(i);
    }
    initColoredPawnNumber();
}

bool ModelTakuzu::putInGrid(int row, int column, State state)
{
    if (column >= 0 && row >= 0) {
        if (column < _gridSize && row < _gridSize) {
            _pawnGrid[row*_gridSize+column].setState(state);
            return true;
        }
    }
    return false;

}

void ModelTakuzu::display()
{
    for(int i =0; i <_gridSize; i++) {
        for(int j =0; j< _gridSize; j++) {
            std::cout << _pawnGrid[i*_gridSize+j].getState();
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void ModelTakuzu::notifyObservers()
{
    for(IObserver * observer: _observers) {
        observer->updateData();
    }
}

void ModelTakuzu::onPawnChanged(const int &id, const State &newState)
{

    if(_pawnGrid[id].getState() == Empty && newState != Empty) {
        _coloredPawn++;
    }
    if (_pawnGrid[id].getState() != Empty && newState == Empty) {
        _coloredPawn--;
    }
    _pawnGrid[id].setState(newState);
    //std::cout << "row:" << id/_gridSize << " column:" << id%_gridSize << " state:" << state << std::endl;
    notifyObservers();
    rulesLoop();
}

std::pair<int, int> ModelTakuzu::countPawnInRow(int row)
{
    int black = 0;
    int white = 0;
    for(int column = 0; column < _gridSize; column++) {
        switch(_pawnGrid[row * _gridSize + column].getState()) {
        case Black:
            black++;
            break;
        case White:
            white++;
            break;
        case Empty:
            break;
        }
    }
    return std::make_pair(black,white);
}

std::pair<int, int> ModelTakuzu::countPawnInColumn(int column)
{
    int black = 0;
    int white = 0;
    for(int row = 0; row < _gridSize; row++) {
        switch(_pawnGrid[row * _gridSize + column].getState()) {
        case Black:
            black++;
            break;
        case White:
            white++;
            break;
        case Empty:
            break;
        }
    }
    return std::make_pair(black,white);
}

bool ModelTakuzu::gridRespectRules()
{
    std::set<std::pair<int,int>> faultyPawnInRow = checkRowSideBySidePawn();
    std::set<std::pair<int,int>> faultyPawnInColumn = checkColumnSideBySidePawn();
    std::set<int> irregularRows = findUnbalancedRows();
    std::set<int> irregularColumns = findUnbalancedColumns();
    std::set<std::pair<int,int>> equivalentRows = findIdenticalRows();
    std::set<std::pair<int,int>> equivalentColumns = findIdenticalColumns();
    return faultyPawnInRow.empty() && faultyPawnInColumn.empty() && irregularRows.empty() && irregularColumns.empty() && equivalentRows.empty() && equivalentColumns.empty();
}

bool ModelTakuzu::gridIsFull()
{
    return _coloredPawn == (_gridSize*_gridSize);
}

void ModelTakuzu::initColoredPawnNumber()
{
    _coloredPawn = 0;
    for (int i =0 ;i< _gridSize*_gridSize;i++) {
        if (_pawnGrid[i].getState()!= Empty) {
            _coloredPawn++;
        }
    }
}

std::pair<int, int> ModelTakuzu::getData(Orientation orientation, int position)
{
    switch(orientation) {
    case Horizontal:
        return countPawnInRow(position);
        break;
    case Vertical:
        return countPawnInColumn(position);
        break; 
    }
    return std::make_pair(-1,-1);
}

void ModelTakuzu::addObserver(IObserver * observer)
{
    _observers.push_back(observer);
}

void ModelTakuzu::removeObserver(IObserver * observer)
{
    _observers.erase(std::remove(_observers.begin(),_observers.end(), observer));
}

void updateVariablesWith(const int & state,int * counter,int * firstIncorrectPawn, const int & valueIncorrectPawn)
{
    if(state != Empty) {
        (*counter)++;
        (*firstIncorrectPawn) = valueIncorrectPawn;
    }
}

void insertIncorrectPawns(std::set<std::pair<int,int>> *faultyPawns,const int & row,const int & firstIncorrectPawn,const int & counter)
{
    for(int i = 0; i < counter; i++) {
        faultyPawns->insert(std::make_pair(row,firstIncorrectPawn + i));
    }

}

std::set<std::pair<int,int>> ModelTakuzu::checkRowSideBySidePawn()
{
    std::set<std::pair<int,int>> faultyPawns;
    int firstIncorrectPawn;
    int counter;
    int previousState, currentState;
    for(int row = 0; row < _gridSize; row++) {
        counter = 0;
        previousState = _pawnGrid[ row * _gridSize].getState();
        updateVariablesWith(previousState,&counter,&firstIncorrectPawn,0);
        for(int column = 1; column < _gridSize; column++) {
            currentState = _pawnGrid[row * _gridSize + column].getState();
            if( currentState == previousState) {
                updateVariablesWith(currentState,&counter,&firstIncorrectPawn,firstIncorrectPawn);
            } else {
                if(counter > 2) {
                    insertIncorrectPawns(&faultyPawns,row,firstIncorrectPawn,counter);
                }
                counter = 0;
                updateVariablesWith(currentState,&counter,&firstIncorrectPawn,column);
                previousState = currentState;
            }
        }
        if(counter > 2) {
            insertIncorrectPawns(&faultyPawns,row,firstIncorrectPawn,counter);
        }
    }
    return faultyPawns;
}

std::set<std::pair<int,int>> ModelTakuzu::checkColumnSideBySidePawn()
{
    std::set<std::pair<int,int>> faultyPawns;
    int firstIncorrectPawn;
    int counter;
    int previousState, currentState;
    for(int column = 0; column < _gridSize; column++) {
        counter = 0;
        previousState = _pawnGrid[column].getState();
        if(previousState) {
            counter++;
            firstIncorrectPawn = 0;
        }
        for(int row = 1; row < _gridSize; row++) {
            currentState = _pawnGrid[row * _gridSize + column].getState();
            if( currentState == previousState) {
                if(previousState != Empty) {
                    counter++;
                }
            } else {
                if(counter > 2) {
                    for(int i = 0; i < counter; i++) {
                        faultyPawns.insert(std::make_pair(firstIncorrectPawn + i,column));
                    }
                }
                counter = 0;
                if(currentState != Empty) {
                    counter++;
                    firstIncorrectPawn = row;
                }
                previousState = currentState;
            }
        }
        if(counter > 2) {
            for(int i = 0; i < counter; i++) {
                faultyPawns.insert(std::make_pair(firstIncorrectPawn + i,column));
            }
        }
    }
    return faultyPawns;
}

std::set<int> ModelTakuzu::findUnbalancedRows()
{
    std::set<int> unbalancedRows;
    int counter = 0;
    int previousState;
    for(int row = 0; row < _gridSize; row++) {
        for(int column = 0; column < _gridSize; column++) {
            previousState = _pawnGrid[row * _gridSize + column].getState();
            switch(previousState) {
            case 1:counter++;
                break;
            case 2:counter--;
                break;
            }
        }
        if (counter) {
            unbalancedRows.insert(row);
        }
        counter = 0;
    }
    return unbalancedRows;
}

std::set<int> ModelTakuzu::findUnbalancedColumns()
{
    std::set<int> unbalancedColumns;
    int counter = 0;
    int previousState;
    for(int column = 0; column < _gridSize; column++) {
        for(int row = 0; row < _gridSize; row++) {
            previousState = _pawnGrid[row * _gridSize + column].getState();
            switch(previousState) {
            case 1:counter++;
                break;
            case 2:counter--;
                break;
            }
        }
        if (counter) {
            unbalancedColumns.insert(column);
        }
        counter = 0;
    }
    return unbalancedColumns;
}

std::set<std::pair<int,int>> ModelTakuzu::findIdenticalColumns()
{
    bool areEqual;
    std::set<std::pair<int,int>> twinColumns;
    for(int column = 0; column < _gridSize - 1; column++) {
        for(int row = 0; row < _gridSize;row++) {
            areEqual = (_pawnGrid[row * _gridSize + column] == _pawnGrid[row * _gridSize + column+1]);
            if(!areEqual) {
                break;
            }
        }
        if (areEqual) {
            twinColumns.insert(std::make_pair(column,column+1));
        }
    }
    return twinColumns;
}

std::set<std::pair<int,int>> ModelTakuzu::findIdenticalRows()
{
    bool areEqual;
    std::set<std::pair<int,int>> twinRows;
    for(int row = 0; row < _gridSize - 1; row++) {
        for(int column = 0; column < _gridSize; column++) {
            areEqual = (_pawnGrid[row * _gridSize + column] == _pawnGrid[(row + 1) * _gridSize + column]);
            if(!areEqual) {
                break;
            }
        }
        if (areEqual) {
            twinRows.insert(std::make_pair(row,row+1));
        }
    }
    return twinRows;
}

void ModelTakuzu::rulesLoop()
{
    if (!isGameFinished()) {
        std::set<std::pair<int,int>> faultyPawnInRow = checkRowSideBySidePawn();
        std::set<std::pair<int,int>> faultyPawnInColumn = checkColumnSideBySidePawn();
        std::set<int> irregularRows = findUnbalancedRows();
        std::set<int> irregularColumns = findUnbalancedColumns();
        std::set<std::pair<int,int>> equivalentRows = findIdenticalRows();
        std::set<std::pair<int,int>> equivalentColumns = findIdenticalColumns();

        if (!faultyPawnInRow.empty()){
            emit incorrectPawnsInRow(faultyPawnInRow);
        }
        if(!faultyPawnInColumn.empty()){
            emit incorrectPawnsInColumn(faultyPawnInColumn);
        }
        if(!irregularRows.empty()) {
            emit unbalancedRows(irregularRows);
        }
        if(!irregularColumns.empty()){
            emit unbalancedColumns(irregularColumns);
        }
        if(!equivalentRows.empty()) {
            emit identicalRows(equivalentRows);
        }
        if (!equivalentColumns.empty()) {
            emit identicalColumns(equivalentColumns);
        }
    }
}

bool ModelTakuzu::isGameFinished()
{
    bool isGameCompleted = gridIsFull() && gridRespectRules();
    if(isGameCompleted) {
        emit notify();
    }
    return isGameCompleted;
}

