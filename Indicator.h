#ifndef INDICATOR_H
#define INDICATOR_H

#include <QWidget>
#include <QPainter>
#include "Constant.h"
#include "ISubject.h"
#include "IObserver.h"


class Indicator : public QWidget,public IObserver
{
    Q_OBJECT
public:
    Indicator(QWidget *parent = nullptr);
    explicit Indicator(int position, ISubject * model, QWidget *parent = nullptr);
    ~Indicator();
    void paintEvent(QPaintEvent *) override;
    void setSubject(ISubject * model);
    void updateData() override;
    void setPosition(const int & position);
    void setOrientation(const Orientation & orientation);
    bool operator==(const Indicator & other);
signals:
private:
    int _blackPawn = 0;
    int _whitePawn = 0;
    int _position = 0;
    Orientation _orientation = Horizontal;
    ISubject * _model;
};

#endif // INDICATOR_H
