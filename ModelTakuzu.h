#ifndef MODELTAKUZU_H
#define MODELTAKUZU_H

#include "Pawn.h"
#include <QObject>

#include <set>
class ModelTakuzu : public QObject
{
    Q_OBJECT
public:
    explicit ModelTakuzu(QObject *parent = nullptr);
    ~ModelTakuzu();

    void setSize(const int & size);
    void initGrid(const int &size);
    void initGrid(const int & size, Pawn* pawns);
    bool putInGrid(int row, int column, State state);
    void display();


    std::set<std::pair<int,int>> checkRowSideBySidePawn();

    std::set<std::pair<int,int>> checkColumnSideBySidePawn();

    std::set<int> findUnbalancedRows();

    std::set<int> findUnbalancedColumns();

    /**
     * @brief check the uniqueness of every columns
     * @return return a set of pair of twin colunms or a set with an unique pair with gridsize
     */
    std::set<std::pair<int,int>> findIdenticalColumns();

    /**
     * @brief check the uniqueness of every rows
     * @return return a set of pair of twin rows or a set with an unique pair with gridsize
     */
    std::set<std::pair<int,int>> findIdenticalRows();

    void rulesLoop();
signals:
    void notify();
    std::set<std::pair<int,int>> incorrectPawnsInRow(std::set<std::pair<int,int>> pawns);
    std::set<std::pair<int,int>> incorrectPawnsInColumn(std::set<std::pair<int,int>> pawns);
    std::set<int> unbalancedRows(std::set<int> rows);
    std::set<int> unbalancedColumns(std::set<int> rows);
    std::set<std::pair<int,int>> identicalRows( std::set<std::pair<int,int>> rows);
    std::set<std::pair<int,int>> identicalColumns( std::set<std::pair<int,int>> columns);

public slots:
    void onPawnChanged(const int & id,const State &state);

private:
    void loadGrid();

    int _gridSize = 0;
    Pawn* _pawnGrid;
};

#endif // MODELTAKUZU_H
