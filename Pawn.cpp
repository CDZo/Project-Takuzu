#include "Pawn.h"
#define PI 3.14159
Pawn::~Pawn()
{
    delete _design;
}

Pawn::Pawn(QWidget *parent) : QWidget(parent)
{
    _design = new BrightCircle;

}

void Pawn::paintEvent(QPaintEvent *) {
    switch (_state){
    case State::Empty:
        _design->displayEmptyPawn(this);
        _design->displayLockPawn(this);
        break;
    case State::Black:
        _design->displayBlackPawn(this);
        _design->displayLockPawn(this);
        break;
    case State::White:
        _design->displayWhitePawn(this);
        _design->displayLockPawn(this);
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
        emit onClicked(_id,_state);
        update();
    }

}

void Pawn::setId(const int &id)
{
    _id = id;
}

void Pawn::setFalse(bool isFalse)
{
    _isFalse = isFalse;
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

QString Pawn::getCompleteState()
{
    QString completeState = "";
    switch (_state){
    case Empty:
        completeState+=".";
        break;
    case White:
        completeState+="W";
        break;
    case Black:
        completeState+="B";
        break;
    }

    if (_isLock){
        completeState+="1";
    }
    else {
        completeState+="0";
    }
    return (completeState);
}

bool Pawn::operator==(const Pawn &other)
{
    return _state == other._state;
}

void Pawn::changeDesignWith(IDesign * newDesign)
{
    _design = newDesign;
}


Pawn::BrightCircle::BrightCircle()
{

}

Pawn::BrightCircle::~BrightCircle()
{

}

void Pawn::BrightCircle::displayEmptyPawn(Pawn *pawn)
{
    QPainter painter(pawn);
    painter.fillRect(pawn->rect(),Qt::gray);
}

void Pawn::BrightCircle::displayWhitePawn(Pawn *pawn)
{
    QPainter painter(pawn);

    QBrush brush(Qt::white);
    QPen pen(Qt::white);
    if(pawn->_isFalse) {
        painter.fillRect(pawn->rect(),Qt::red);
    } else {
        painter.fillRect(pawn->rect(),Qt::gray);
    }
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawEllipse(pawn->width()*0.05,pawn->height()*0.05,pawn->width()*0.9,pawn->height()*0.9);
}

void Pawn::BrightCircle::displayBlackPawn(Pawn *pawn)
{
    QPainter painter(pawn);
    QBrush brush(Qt::black);
    if(pawn->_isFalse) {
        painter.fillRect(pawn->rect(),Qt::red);
    } else {
        painter.fillRect(pawn->rect(),Qt::gray);
    }
    painter.setBrush(brush);
    painter.drawEllipse(pawn->width()*0.05,pawn->height()*0.05,pawn->width()*0.9,pawn->height()*0.9);
}

void Pawn::BrightCircle::displayLockPawn(Pawn *pawn)
{
    if (pawn->_isLock) {
        QPainter painter(pawn);
        QBrush brush(Qt::gray);
        QPen pen(Qt::gray);

        if(pawn->_isFalse) {
            pen.setColor(Qt::red);
            brush.setColor(Qt::red);
        } else {
            pen.setColor(Qt::gray);
            brush.setColor(Qt::gray);
        }
        painter.setBrush(brush);
        painter.setPen(pen);

        int marginX = pawn->width() * 0.45;
        int marginY = pawn->height() * 0.45;
        int diameterX = pawn->width()-2*marginX;
        int diameterY = pawn->height() -2*marginY;

        painter.drawEllipse(marginX, marginY, diameterX, diameterY);
    }
}


Pawn::IDesign::~IDesign()
{

}

Pawn::BrightSquare::BrightSquare()
{

}

Pawn::BrightSquare::~BrightSquare()
{

}

void Pawn::BrightSquare::displayEmptyPawn(Pawn *pawn)
{
    QPainter painter(pawn);
    painter.fillRect(pawn->rect(),Qt::gray);
}

void Pawn::BrightSquare::displayWhitePawn(Pawn *pawn)
{
    QPainter painter(pawn);

    QBrush brush(Qt::white);
    QPen pen(Qt::white);
    if(pawn->_isFalse) {
        painter.fillRect(pawn->rect(),Qt::red);
    } else {
        painter.fillRect(pawn->rect(),Qt::gray);
    }
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(pawn->width()*0.05,pawn->height()*0.05,pawn->width()*0.9,pawn->height()*0.9);
}

void Pawn::BrightSquare::displayBlackPawn(Pawn *pawn)
{
    QPainter painter(pawn);
    QBrush brush(Qt::black);
    if(pawn->_isFalse) {
        painter.fillRect(pawn->rect(),Qt::red);
    } else {
        painter.fillRect(pawn->rect(),Qt::gray);
    }
    painter.setBrush(brush);
    painter.drawRect(pawn->width()*0.05,pawn->height()*0.05,pawn->width()*0.9,pawn->height()*0.9);
}

void Pawn::BrightSquare::displayLockPawn(Pawn *pawn)
{
    if (pawn->_isLock) {
        QPainter painter(pawn);
        QBrush brush(Qt::gray);
        QPen pen(Qt::gray);

        if(pawn->_isFalse) {
            pen.setColor(Qt::red);
            brush.setColor(Qt::red);
        } else {
            pen.setColor(Qt::gray);
            brush.setColor(Qt::gray);
        }
        painter.setBrush(brush);
        painter.setPen(pen);

        int marginX = pawn->width() * 0.45;
        int marginY = pawn->height() * 0.45;
        int diameterX = pawn->width()-2*marginX;
        int diameterY = pawn->height() -2*marginY;

        painter.drawEllipse(marginX, marginY, diameterX, diameterY);
    }
}

Pawn::DarkCircle::DarkCircle()
{

}

Pawn::DarkCircle::~DarkCircle()
{

}

void Pawn::DarkCircle::displayEmptyPawn(Pawn *pawn)
{
    QPainter painter(pawn);
    painter.fillRect(pawn->rect(),Qt::black);
}

void Pawn::DarkCircle::displayWhitePawn(Pawn *pawn)
{
    QPainter painter(pawn);
    QBrush brush(Qt::white);
    QPen pen(Qt::white);
    if(pawn->_isFalse) {
        painter.fillRect(pawn->rect(),Qt::red);
    } else {
        painter.fillRect(pawn->rect(),Qt::black);
    }
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawEllipse(pawn->width()*0.05,pawn->height()*0.05,pawn->width()*0.9,pawn->height()*0.9);
}

void Pawn::DarkCircle::displayBlackPawn(Pawn *pawn)
{
    QPainter painter(pawn);
    QBrush brush(Qt::black);
    QPen pen(Qt::gray);
    if(pawn->_isFalse) {
        painter.fillRect(pawn->rect(),Qt::red);
    } else {
        painter.fillRect(pawn->rect(),Qt::black);
    }
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawEllipse(pawn->width()*0.05,pawn->height()*0.05,pawn->width()*0.9,pawn->height()*0.9);
}

void Pawn::DarkCircle::displayLockPawn(Pawn *pawn)
{
    if (pawn->_isLock) {
        QPainter painter(pawn);
        QBrush brush(Qt::gray);
        QPen pen(Qt::gray);

        if(pawn->_isFalse) {
            pen.setColor(Qt::red);
            brush.setColor(Qt::red);
        } else {
            pen.setColor(Qt::gray);
            brush.setColor(Qt::gray);
        }
        painter.setBrush(brush);
        painter.setPen(pen);

        int marginX = pawn->width() * 0.45;
        int marginY = pawn->height() * 0.45;
        int diameterX = pawn->width()-2*marginX;
        int diameterY = pawn->height() -2*marginY;

        painter.drawEllipse(marginX, marginY, diameterX, diameterY);
    }
}
