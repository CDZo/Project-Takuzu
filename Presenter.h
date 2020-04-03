#ifndef PRESENTER_H
#define PRESENTER_H
#include <QObject>
#include "ModelTakuzu.h"
#include "View.h"
class Presenter: public QObject
{
    Q_OBJECT
public:
    Presenter();
    ~Presenter();
    void createGrid(const int & difficulty);
    void show();
private:
    void resetFalsePawns();
    View *_view;
    ModelTakuzu *_model;
    Pawn *_visualPawns;
    int _size = 0;
public slots:
    void onPawnClicked(const int & id, const State & state);
    void onIncorrectPawnsInRow(const std::set<std::pair<int,int>> pawns);
    void onIncorrectPawnsInColumn(const std::set<std::pair<int,int>> pawns);
    void onUnbalancedRows(std::set<int> rows);
    void onUnbalancedColumns(std::set<int> columns);
    void onIdenticalRows(std::set<std::pair<int,int>> rows);
    void onIdenticalColumns(std::set<std::pair<int,int>> columns);


signals:
    void pawnChanged(const int & id, const State & state);
};

#endif
