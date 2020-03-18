#ifndef MODELTAKUZU_H
#define MODELTAKUZU_H

#include <QObject>
#include "Pawn.h"
class ModelTakuzu : public QObject
{
    Q_OBJECT
public:
    explicit ModelTakuzu(QObject *parent = nullptr);
    void isFinalCorrect();
    void isLignCorrect(const int & lign);
    void isColumnCorrect(const int & column);
    void setSize(const int & size);
    void initGrid(const int &size);

signals:

public slots:
    void onPawnChanged(const int & lign, const int & column,const int &state);

private:
    void loadGrid();
    /*2d array in oned */
    Pawn *_pawnGrid;
    int _gridSize = 0;
};

#endif // MODELTAKUZU_H
