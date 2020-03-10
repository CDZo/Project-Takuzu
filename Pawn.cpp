#include "Pawn.h"
#define PI 3.14159
Pawn::Pawn(QWidget *parent) : QWidget(parent)
{
   _isLock = false;
   _state = empty;
}

void Pawn::paintEvent(QPaintEvent *) {
   QPainter painter(this);
   painter.fillRect(rect(),Qt::white);
   painter.drawArc(rect(),0,360*16);
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
    std::cout << "J'ai été cliqué " << _state << std::endl;
}
