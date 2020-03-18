#include "ModelTakuzu.h"
#include <iostream>
ModelTakuzu::ModelTakuzu(QObject *parent) : QObject(parent)
{

}

void ModelTakuzu::setSize(const int &size)
{
    _gridSize = size;

}

void ModelTakuzu::initGrid(const int &size)
{
    _gridSize = size;
    _pawnGrid = new Pawn[size * size];
    _stateGrid = new int[size * size];
}

void ModelTakuzu::onPawnChanged(const int &lign, const int &column, const int &state)
{
    std::cout <<"old state:" <<  _stateGrid[lign * _gridSize + column] << std::endl;
    std::cout << "lign:" << lign << " column:" << column << " state:" << state << std::endl;
    _stateGrid[lign * _gridSize + column] = state;
    std::cout <<"new state:" <<  _stateGrid[lign * _gridSize + column] << std::endl;
}
