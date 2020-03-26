#include "Pawn.h"
#define PI 3.14159
Pawn::Pawn(QWidget *parent) : QWidget(parent)
{
    _isLock = false;
    _state = State::Empty;
    _row = -1;
    _column = -1;
}

void Pawn::paintEvent(QPaintEvent *) {
    switch (_state){
    case State::Empty:
        displayEmptyPawn();
        displayLockPawn();
        break;
    case State::Black:
        displayBlackPawn();
        displayLockPawn();
        break;
    case State::White:
        displayWhitePawn();
        displayLockPawn();
        break;
    }
}

void Pawn::mousePressEvent(QMouseEvent *) {
    if (!_isLock) {
        switch (_state){
        case White:
            _state = Empty;
            break;
        case Black:
            _state = White;
            break;
        case Empty:
            _state = Black;
            break;
        }
        emit onClicked(_row,_column,_state);
        update();
    }

}

void Pawn::setPosition(const int &row, const int &column)
{
    _row = row;
    _column = column;
}

void Pawn::setLock(bool isLock)
{
    _isLock = isLock;
}

void Pawn::setState(const State &state)
{
    _state = State(state);
}

State Pawn::getState()
{
    return _state;
}

bool Pawn::operator==(const Pawn &other)
{
    return _state == other._state;
}

void Pawn::displayWhitePawn()
{
    QPainter painter(this);

    QBrush brush(Qt::white);
    QPen pen(Qt::white);

    painter.fillRect(rect(),Qt::gray);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawEllipse(width()*0.05,height()*0.05,width()*0.9,height()*0.9);
}

void Pawn::displayBlackPawn()
{
    QPainter painter(this);
    QBrush brush(Qt::black);

    painter.fillRect(rect(),Qt::gray);
    painter.setBrush(brush);
    painter.drawEllipse(width()*0.05,height()*0.05,width()*0.9,height()*0.9);

}

void Pawn::displayEmptyPawn()
{
    QPainter painter(this);
    painter.fillRect(rect(),Qt::gray);
}

void Pawn::displayLockPawn(){
    if (_isLock) {
        QPainter painter(this);
        QBrush brush(Qt::green);
        QPen pen(Qt::green);
        painter.setBrush(brush);
        painter.setPen(pen);

        int marginX = width() * 0.4;
        int marginY = height() * 0.4;
        int radiusX = width() * 0.1;
        int radiusY = height() * 0.1;

        painter.drawEllipse(marginX, marginY, radiusX * 2 , radiusY * 2);
    }
}
