#include "Indicator.h"

Indicator::Indicator(QWidget *parent): QWidget(parent)
{
    _position = -1;
}

Indicator::Indicator(int position, ISubject * model,QWidget *parent) : QWidget(parent)
{
    _position = position;
    _model = model;
}

Indicator::~Indicator()
{
    _model = nullptr;
    delete _model;
}

void Indicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);
    //painter.fillRect(rect(),Qt::green);
    switch(_orientation) {
    case Horizontal:
        drawHorizontally();
        break;
    case Vertical:
        drawVertically();
        break;
    }

}

void Indicator::setSubject(ISubject *model)
{
    _model = model;
}

void Indicator::updateData()
{
    std::pair<int,int> blackAndWhite= _model->getData(_orientation,_position);
    _blackPawn = blackAndWhite.first;
    _whitePawn = blackAndWhite.second;
    update();
}

void Indicator::setPosition(const int &position)
{
    _position = position;
}

void Indicator::setOrientation(const Orientation & orientation)
{
    _orientation = orientation;
}

bool Indicator::operator==(const Indicator &other)
{
    return _orientation == other._orientation && _position == other._position;
}

void Indicator::drawHorizontally()
{
    QPainter painter(this);
    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);
    painter.fillRect(rect(),Qt::gray);
    QRect blackRect(0,0,width()/2,height());
    QRect whiteRect(width()/2,1,width()/2,height()-2);

    painter.fillRect(blackRect,Qt::black);
    painter.fillRect(whiteRect,Qt::white);

    painter.setPen(Qt::white);
    painter.drawText(blackRect,Qt::AlignCenter,QString::number(_blackPawn));
    painter.setPen(Qt::black);
    painter.drawText(whiteRect,Qt::AlignCenter,QString::number(_whitePawn));

}

void Indicator::drawVertically()
{
    QPainter painter(this);
    QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);
    painter.fillRect(rect(),Qt::gray);
    QRect blackRect(0,0,width(),height()/2);
    QRect whiteRect(1,height()/2,width()-2,height()/2);

    painter.fillRect(blackRect,Qt::black);
    painter.fillRect(whiteRect,Qt::white);

    painter.setPen(Qt::white);
    painter.drawText(blackRect,Qt::AlignCenter,QString::number(_blackPawn));
    painter.setPen(Qt::black);
    painter.drawText(whiteRect,Qt::AlignCenter,QString::number(_whitePawn));
}
