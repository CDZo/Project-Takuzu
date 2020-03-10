#ifndef PAWN_H
#define PAWN_H

#include <QWidget>
#include <QPainter>
#include <iostream>
#include <QPainterPath>
#include <QBrush>

class Pawn : public QWidget
{
    Q_OBJECT
public:
    explicit Pawn(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;

signals:

public slots:

private:
    void displayEmptyPawn();
    void displayWhitePawn();
    void displayBlackPawn();
    enum State {empty, black, white};
    State _state;
    bool _isLock;
};

#endif // PAWN_H
