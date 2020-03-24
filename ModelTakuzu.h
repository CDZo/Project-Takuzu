#ifndef MODELTAKUZU_H
#define MODELTAKUZU_H

#include <QObject>
#include "Pawn.h"
class ModelTakuzu : public QObject
{
    Q_OBJECT
public:
    explicit ModelTakuzu(QObject *parent = nullptr);
    ~ModelTakuzu();
    void isFinalCorrect();
    void isLignCorrect(const int & lign);
    void isColumnCorrect(const int & column);

    void setSize(const int & size);
    void initGrid(const int &size);
    bool putInGrid(int lign, int column, int state);
    void display();

    /**
     * @brief check on every ligns for more than 2 pawn side by side
     * @return the lign where it first detects more than 2 pawn side by side or gridsizes;
     */
    int checkLignSideBySidePawn();

    /**
     * @brief check on every column for more than 2 pawn side by side
     * @return
     */
    int checkColumnSideBySidePawn();

    int checkNumberLign();
    bool checkNumberColumn();

    bool isAllColumnUnique();
    bool isAllLignUnique();

signals:
    void notify();

public slots:
    void onPawnChanged(const int & lign, const int & column,const int &state);

private:
    void loadGrid();


    /*2d array in oned */
    Pawn *_pawnGrid;
    int _gridSize = 0;
};

#endif // MODELTAKUZU_H
