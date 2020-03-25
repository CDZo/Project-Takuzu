#ifndef MODELTAKUZU_H
#define MODELTAKUZU_H

#include <QObject>
#include "Pawn.h"
#include <set>
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
     * @return the lign where it first detects more than 2 pawn side by side or gridsize
     */
    int checkLignSideBySidePawn();

    /**
     * @brief check on every column for more than 2 pawn side by side
     * @return the column where it first detects more than 2 pawnside by side or gridsize
     */
    int checkColumnSideBySidePawn();

    /**
     * @brief check on every lign that colors and numbers of pawn are balanced
     * @return the first lign unbalanced or gridsize
     */
    int checkBalancedNumberLign();

    /**
     * @brief check on every column that colors and numbers of pawn are balanced
     * @return the first column unbalanced or gridsize
     */
    int checkBalancedNumberColumn();

    /**
     * @brief check the uniqueness of every columns
     * @return return a set of pair of twin colunms or a set with an unique pair with gridsize
     */
    std::set<std::pair<int,int>> isAllColumnUnique();

    /**
     * @brief check the uniqueness of every ligns
     * @return return a set of pair of twin ligns or a set with an unique pair with gridsize
     */
    std::set<std::pair<int,int>> isAllLignUnique();

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
