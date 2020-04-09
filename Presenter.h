#ifndef PRESENTER_H
#define PRESENTER_H
#include <QObject>
#include "ModelTakuzu.h"
#include "View.h"
#include "NewGame.h"
#include <QSettings>

class Presenter: public QObject
{
    Q_OBJECT
public:
    Presenter();
    ~Presenter();
    Pawn * initVisualPawnWith(const int & gridSize,const Difficulty & difficulty);
    void saveGrid(QString name);
    void loadSavedGrid(QString name);
    void show();
private:
    void resetFalsePawns();
    void initConnectionWithModel();

    void initNewGrid(const int & size, const Difficulty & difficulty);
    Indicator * initNewIndicator(const int & gridSize);
    void replaceGrid(const int & size, const Difficulty & difficulty);

    View *_view;
    ModelTakuzu *_model;
    Pawn *_visualPawns;
    Indicator * _indicators;

    NewGame * _newGame;
    Difficulty _newDifficulty = Easy;
    int _newSize = 6;


    int _gridSize = 0;
    int _indicatorSize = 0;
    QSettings _save;

public slots:
    void onPawnClicked(const int & id, const State & state);
    void onIncorrectPawnsInRow(const std::set<std::pair<int,int>> pawns);
    void onIncorrectPawnsInColumn(const std::set<std::pair<int,int>> pawns);
    void onUnbalancedRows(std::set<int> rows);
    void onUnbalancedColumns(std::set<int> columns);
    void onIdenticalRows(std::set<std::pair<int,int>> rows);
    void onIdenticalColumns(std::set<std::pair<int,int>> columns);
    void onGameFinished();


    void onReceivingNewSize(int index);
    void onReceivingNewDifficulty(int index);

    void onPressedNew();

signals:
    void pawnChanged(const int & id, const State & state);
};

#endif
