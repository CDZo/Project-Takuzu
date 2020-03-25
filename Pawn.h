#ifndef PAWN_H
#define PAWN_H

#include <QWidget>
#include <QPainter>
#include <iostream>
#include <QPainterPath>
#include <QBrush>
#include "State.h"
class Pawn : public QWidget
{
    Q_OBJECT
public:
    explicit Pawn(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void setPosition(const int &lign, const int & column);
    void setState(const State &state);
    int getState();
    bool operator==(const Pawn & other);

signals:
void onClicked(const int lign,const int column,const State state);

public slots:

private:
    void displayEmptyPawn();
    void displayWhitePawn();
    void displayBlackPawn();
    State _state = Empty;
    bool _isLock = false;
};

#endif // PAWN_H
