#include "Pawn.h"
#define PI 3.14159
Pawn::Pawn(QWidget *parent) : QWidget(parent)
{
    _isLock = false;
    _state = State::Empty;
}

void Pawn::paintEvent(QPaintEvent *) {
    switch (_state){
    case State::Empty:
        displayEmptyPawn();
        break;
    case State::Black:
        displayBlackPawn();
        break;
    case State::White:
        displayWhitePawn();
        break;
    }
}

void Pawn::mousePressEvent(QMouseEvent *) {

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
    emit onClicked(0,0,_state);
    update();
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

