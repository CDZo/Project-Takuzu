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
    void setPosition(const int &lign, const int & column);
    void setState(const int &state);
    int getState();

signals:
void onClicked(const int lign,const int column,const int state);

public slots:

private:
    void displayEmptyPawn();
    void displayWhitePawn();
    void displayBlackPawn();
    enum State {empty, black, white};
    State _state = empty;
    bool _isLock = false;
};

#endif // PAWN_H
