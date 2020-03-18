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
}

void ModelTakuzu::onPawnChanged(const int &lign, const int &column, const int &state)
{
    std::cout <<"old state:" <<  _pawnGrid[lign * _gridSize + column].getState() << std::endl;
    std::cout << "lign:" << lign << " column:" << column << " state:" << state << std::endl;
    _pawnGrid[lign * _gridSize + column].setState(state);
    std::cout <<"new state:" <<  _pawnGrid[lign * _gridSize + column].getState() << std::endl;
}
