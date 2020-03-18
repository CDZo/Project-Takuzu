#include "Pawn.h"
#define PI 3.14159
Pawn::Pawn(QWidget *parent) : QWidget(parent)
{
    _isLock = false;
    _state = empty;
}

void Pawn::paintEvent(QPaintEvent *) {
    switch (_state){
    case empty:
        displayEmptyPawn();
        break;
    case black:
        displayBlackPawn();
        break;
    case white:
        displayWhitePawn();
        break;
    }
}

void Pawn::mousePressEvent(QMouseEvent *) {

    switch (_state){
    case white:
        _state = empty;
        break;
    case black:
        _state = white;
        break;
    case empty:
        _state = black;
        break;
    }
    emit onClicked(0,0,_state);
    update();
}


void Pawn::displayWhitePawn()
{
    QPainter painter(this);

    QBrush brush(Qt::white);
    QPen pen(Qt::white);

    painter.fillRect(rect(),Qt::gray);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawEllipse(rect());
}

void Pawn::displayBlackPawn()
{
    QPainter painter(this);
    QBrush brush(Qt::black);

    painter.fillRect(rect(),Qt::gray);
    painter.setBrush(brush);
    painter.drawEllipse(rect());
}
void Pawn::displayEmptyPawn()
{
    QPainter painter(this);
    painter.fillRect(rect(),Qt::gray);
}
