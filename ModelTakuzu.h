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

    void setSize(const int & size);
    void initGrid(const int &size);
    bool putInGrid(int row, int column, int state);
    void display();


    std::set<std::pair<int,int>> checkRowSideBySidePawn();

    std::set<std::pair<int,int>> checkColumnSideBySidePawn();

    std::set<int> findUnbalancedRows();

    std::set<int> findUnbalancedColumns();

    /**
     * @brief check the uniqueness of every columns
     * @return return a set of pair of twin colunms or a set with an unique pair with gridsize
     */
    std::set<std::pair<int,int>> isAllColumnUnique();

    /**
     * @brief check the uniqueness of every rows
     * @return return a set of pair of twin rows or a set with an unique pair with gridsize
     */
    std::set<std::pair<int,int>> isAllRowUnique();

signals:
    void notify();

public slots:
    void onPawnChanged(const int & row, const int & column,const State &state);

private:
    void loadGrid();


    /*2d array in oned */
    Pawn *_pawnGrid;
    int _gridSize = 0;
};

#endif // MODELTAKUZU_H
