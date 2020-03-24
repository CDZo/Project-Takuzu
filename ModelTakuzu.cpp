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
        if (column < _gridSize || lign < _gridSize) {
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
    _pawnGrid[lign * _gridSize + column
            ].setState(state);
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
