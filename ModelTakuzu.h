#ifndef MODELTAKUZU_H
#define MODELTAKUZU_H

#include <QObject>
#include "Pawn.h"
#include "Indicator.h"
#include "IObserver.h"
#include "ISubject.h"
#include <set>

class ModelTakuzu : public QObject, public ISubject
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
    /**
     * @brief isGameFinished check rules and number of not Empty pawns.
     * @return true and emit signal notity or false.
     */
    bool isGameFinished();

    void notifyObservers() override;
    void addObserver(IObserver * observer) override;
    //TODO to test
    //void removeObserver(IObserver * observer) override;
    std::pair<int, int> getData(Orientation orientation, int position) override;
    void initColoredPawnNumber();

signals:
    void notify();
    std::set<std::pair<int,int>> incorrectPawnsInRow(std::set<std::pair<int,int>> pawns);
    std::set<std::pair<int,int>> incorrectPawnsInColumn(std::set<std::pair<int,int>> pawns);
    std::set<int> unbalancedRows(std::set<int> rows);
    std::set<int> unbalancedColumns(std::set<int> rows);
    std::set<std::pair<int,int>> identicalRows( std::set<std::pair<int,int>> rows);
    std::set<std::pair<int,int>> identicalColumns( std::set<std::pair<int,int>> columns);


public slots:
    void onPawnChanged(const int & id,const State &newState);

private:
    std::pair<int,int> countPawnInRow(int row);
    std::pair<int,int> countPawnInColumn(int column);

    void loadGrid();
    bool gridRespectRules();
    bool gridIsFull();
    std::list<IObserver*> _observers;
    int _gridSize = 0;
    int _coloredPawn = 0;
    Pawn* _pawnGrid;

};

#endif // MODELTAKUZU_H
