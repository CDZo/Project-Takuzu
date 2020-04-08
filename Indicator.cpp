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
    font.setPixelSize(36);
    painter.setFont(font);
    //painter.fillRect(rect(),Qt::green);
    switch(_orientation) {
    case Horizontal:
        painter.drawText(rect(),Qt::AlignCenter,QString::number(_blackPawn) +" "+ QString::number(_whitePawn));
        break;
    case Vertical:
        painter.drawText(rect(),Qt::AlignCenter,QString::number(_blackPawn) +"\n"+ QString::number(_whitePawn));
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
