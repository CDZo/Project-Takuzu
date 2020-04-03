#ifndef PAWN_H
#define PAWN_H

#include <QWidget>
#include <QPainter>
#include <iostream>
#include <QPainterPath>
#include <QBrush>
#include "Constant.h"
class Pawn : public QWidget
{
    Q_OBJECT
public:
    explicit Pawn(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void setId(const int & id);
    void setFalse(bool isFalse);
    void setLock(bool isLock);
    void setState(const State &state);
    State getState();
    bool operator==(const Pawn & other);

signals:
void onClicked(const int id, const State state);

public slots:

private:
    void displayEmptyPawn();
    void displayWhitePawn();
    void displayBlackPawn();
    void displayLockPawn();
    State _state = State::Empty;
    bool _isLock = false;
    bool _isFalse = false;
    int _id = -1;

private:
    class Design {
        void displayEmptyPawn();
        void displayWhitePawn();
        void displayBlackPawn();
        void displayLockPawn();
    };
};

#endif // PAWN_H
