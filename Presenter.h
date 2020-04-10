#ifndef PRESENTER_H
#define PRESENTER_H
#include <QObject>
#include <QSettings>
#include "ModelTakuzu.h"
#include "View.h"
#include "NewGame.h"
#include "Load.h"
#include "Save.h"
#include "Error.h"
#include "Option.h"

class Presenter: public QObject
{
    Q_OBJECT
public:
    Presenter();
    ~Presenter();
    Pawn * initVisualPawnWith(const int & gridSize,const Difficulty & difficulty);
    void saveGrid(QString name);
    void loadSavedGame(QString name);
    void show();

private:
    void resetFalsePawns();
    void changeAllPawnDesignWith(const PawnDesign & newDesign);
    void initConnectionWithModel();

    void initNewGrid(const int & size, const Difficulty & difficulty);
    Indicator * initNewIndicator(const int & gridSize);
    void replaceWithNewGrid(const int & size, const Difficulty & difficulty);
    void replaceGrid(const int & size, Pawn* pawns);
    Pawn * loadSavedGrid(QString name);
    void changeTimerWithSavedTimer(QString name);
    void initViews();
    void initConnectionWithViews();
    void setIncorrectRowPawnWith(const bool &value,const std::set<std::pair<int, int>> &pawns);
    void setIncorrectColumnPawnWith(const bool &value,const std::set<std::pair<int, int>> &pawns);
    void setColumnWith(const bool &value, std::set<int> columns);
    void setRowWith(const bool &value, std::set<int> rows);
private:

    View *_view;
    ModelTakuzu *_model;
    Pawn *_visualPawns;
    Indicator * _indicators;
    int _newSize = 6;
    Difficulty _newDifficulty = Easy;

    Error * _error;
    NewGame * _newGame;
    Save * _saveDialog;
    Load * _loadDialog;
    Option * _option;

    QString _saveName;
    QString _loadName;


    int _gridSize = 0;
    int _indicatorSize = 0;
    QSettings * _save;

    PawnDesign _pawnDesign = PawnDesign::BrightCircle;
    PawnDesign _newPawnDesign = PawnDesign::BrightCircle;

    Qt::CheckState _needHelpIncorrectInRowColumn = Qt::CheckState::Unchecked;
    Qt::CheckState _newHelpIncorrectInRowColumn = Qt::CheckState::Unchecked;

    Qt::CheckState _needHelpUnbalancedRowColumn = Qt::CheckState::Unchecked;
    Qt::CheckState _newHelpUnbalancedRowColumn = Qt::CheckState::Unchecked;

    Qt::CheckState _needHelpIdenticalRowColunm = Qt::CheckState::Unchecked;
    Qt::CheckState _newHelpIdenticalRowColunm = Qt::CheckState::Unchecked;


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

    void onReceivingSaveName(QString text);

    void onReceivingLoadName(QString text);

    void onPressedSave();
    void onPressedLoad();
    void onPressedNew();
    void onPressedOption();

    void onDesignChanged(PawnDesign design);
    void onHelpIncorrectInRowColumn(Qt::CheckState state);
    void onHelpUnbalancedRowColumn(Qt::CheckState state);
    void onHelpIdenticalRowColumn(Qt::CheckState state);


signals:
    void pawnChanged(const int & id, const State & state);
};

#endif
