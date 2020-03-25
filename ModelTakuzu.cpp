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


bool ModelTakuzu::putInGrid(int lign, int column, int state)
{
    if (column >= 0 && lign >= 0) {
        if (column < _gridSize && lign < _gridSize) {
            _pawnGrid[lign*_gridSize+column].setState(state);
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

void ModelTakuzu::onPawnChanged(const int &lign, const int &column, const int &state)
{
    std::cout <<"old state:" <<  _pawnGrid[lign * _gridSize + column].getState() << std::endl;
    std::cout << "lign:" << lign << " column:" << column << " state:" << state << std::endl;
    _pawnGrid[lign * _gridSize + column].setState(state);
    std::cout <<"new state:" <<  _pawnGrid[lign * _gridSize + column].getState() << std::endl;
}

int ModelTakuzu::checkLignSideBySidePawn()
{
    int counter = 0;
    int previousState;
    for(int i = 0; i < _gridSize; i++) {
        previousState = _pawnGrid[i*_gridSize].getState();
        if(previousState != 0) {
            counter++;
        }

        for(int j = 1; j < _gridSize; j++) {
            if(_pawnGrid[i*_gridSize+j].getState() == previousState) {
                if(previousState != 0) {
                    counter++;
                }
                if (counter > 2) {
                    return i;
                }
            } else {
                previousState = _pawnGrid[i*_gridSize+j].getState();
                counter = 1;
            }
        }
        counter = 0;
    }
    return _gridSize;
}

int ModelTakuzu::checkColumnSideBySidePawn()
{
    int counter = 0;
    int previousState;
    for(int column = 0; column < _gridSize; column++) {
        previousState = _pawnGrid[column].getState();
        if(previousState != 0) {
            counter++;
        }
        for(int lign = 1; lign < _gridSize; lign++) {
            if(_pawnGrid[lign * _gridSize + column].getState() == previousState) {
                if(previousState != 0) {
                    counter++;
                }
                if (counter > 2) {
                    return column;
                }
            } else {
                previousState = _pawnGrid[lign*_gridSize+column].getState();
                counter = 1;
            }
        }
        counter = 0;
    }
    return _gridSize;
}

int ModelTakuzu::checkBalancedNumberLign()
{
    int counter = 0;
    int previousState;
    for(int lign = 0; lign < _gridSize; lign++) {
        for(int column = 0; column < _gridSize; column++) {
            previousState = _pawnGrid[lign * _gridSize + column].getState();
            switch(previousState) {
            case 1:counter++;
                break;
            case 2:counter--;
                break;
            }
        }
        if (counter != 0) {
            return lign;
        }
        counter = 0;
    }
    return _gridSize;
}

int ModelTakuzu::checkBalancedNumberColumn()
{
    int counter = 0;
    int previousState;
    for(int column = 0; column < _gridSize; column++) {
        for(int lign = 0; lign < _gridSize; lign++) {
            previousState = _pawnGrid[lign * _gridSize + column].getState();
            switch(previousState) {
            case 1:counter++;
                break;
            case 2:counter--;
                break;
            }
        }
        if (counter != 0) {
            return column;
        }
        counter = 0;
    }
    return _gridSize;
}

std::set<std::pair<int,int>> ModelTakuzu::isAllColumnUnique()
{
    bool areEqual;
    std::set<std::pair<int,int>> twinColumns;
    for(int column = 0; column < _gridSize - 1; column++) {
        for(int lign = 0; lign < _gridSize;lign++) {
            areEqual = (_pawnGrid[lign * _gridSize + column] == _pawnGrid[lign * _gridSize + column+1]);
            if(!areEqual) {
                break;
            }
        }
        if (areEqual) {
            twinColumns.insert(std::make_pair(column,column+1));
        }
    }
    if (twinColumns.empty()) {
        twinColumns.insert(std::make_pair(_gridSize,_gridSize));
    }
    return twinColumns;
}

std::set<std::pair<int,int>> ModelTakuzu::isAllLignUnique()
{
    bool areEqual;
    std::set<std::pair<int,int>> twinLigns;
    for(int lign = 0; lign < _gridSize - 1; lign++) {
        for(int column = 0; column < _gridSize; column++) {
            areEqual = (_pawnGrid[lign * _gridSize + column] == _pawnGrid[(lign + 1) * _gridSize + column]);
            if(!areEqual) {
                break;
            }
        }
        if (areEqual) {
            twinLigns.insert(std::make_pair(lign,lign+1));
        }
    }
    if (twinLigns.empty()) {
        twinLigns.insert(std::make_pair(_gridSize,_gridSize));
    }
    return twinLigns;
}
