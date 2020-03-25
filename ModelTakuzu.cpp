#include "ModelTakuzu.h"
#include <iostream>
ModelTakuzu::ModelTakuzu(QObject *parent) : QObject(parent)
{

}

ModelTakuzu::~ModelTakuzu()
{
    delete [] _pawnGrid;
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

bool ModelTakuzu::putInGrid(int row, int column, int state)
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

void ModelTakuzu::onPawnChanged(const int &row, const int &column, const int &state)
{
    std::cout <<"old state:" <<  _pawnGrid[row * _gridSize + column].getState() << std::endl;
    std::cout << "row:" << row << " column:" << column << " state:" << state << std::endl;
    _pawnGrid[row * _gridSize + column].setState(state);
    std::cout <<"new state:" <<  _pawnGrid[row * _gridSize + column].getState() << std::endl;
}

void updateVariablesWith(const int & state,int * counter,int * firstIncorrectPawn, const int & valueIncorrectPawn)
{
    if(state) {
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
                if(previousState) {
                    counter++;
                }
            } else {
                if(counter > 2) {
                    for(int i = 0; i < counter; i++) {
                        faultyPawns.insert(std::make_pair(firstIncorrectPawn + i,column));
                    }
                }
                counter = 0;
                if(currentState) {
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

std::set<std::pair<int,int>> ModelTakuzu::isAllColumnUnique()
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

std::set<std::pair<int,int>> ModelTakuzu::isAllRowUnique()
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
