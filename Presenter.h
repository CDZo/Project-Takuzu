#ifndef PRESENTER_H
#define PRESENTER_H
#include <QObject>
#include <QSettings>
#include "ModelTakuzu.h"
#include "View.h"
#include "NewGame.h"
#include "Load.h"
#include "Save.h"
#include "Option.h"
#include "Information.h"

class Presenter: public QObject
{
    Q_OBJECT
public:
    Presenter();
    ~Presenter();
    void show();
    Pawn * initVisualPawnWith(const int & gridSize,const Difficulty & difficulty);
    void saveGrid(QString name);
    void loadSavedGame(QString name);

private:
    void initNewGrid(const int & size, const Difficulty & difficulty);
    void initViews();
    void initConnectionWithViews();
    void initConnectionWithModel();

    void replaceWithNewGrid(const int & size, const Difficulty & difficulty);
    Indicator * initNewIndicator(const int & gridSize);
    void resetFalsePawns();
    void changeAllPawnDesignWith(const PawnDesign & newDesign);

    void replaceGrid(const int & size, Pawn* pawns);
    Pawn * loadSavedGrid(QString name);
    void changeTimerWithSavedTimer(QString name);

    void setIncorrectRowPawnWith(const bool &value,const std::set<std::pair<int, int>> &pawns);
    void setIncorrectColumnPawnWith(const bool &value,const std::set<std::pair<int, int>> &pawns);
    void setColumnWith(const bool &value, std::set<int> columns);
    void setRowWith(const bool &value, std::set<int> rows);
    void setIndicatorVisibilityTo(bool value);
private:

    View *_view;
    ModelTakuzu *_model;
    Pawn *_visualPawns;
    Indicator * _indicators;
    int _newSize = 6;
    Difficulty _newDifficulty = Easy;

    NewGame * _newGame;
    Save * _saveDialog;
    Load * _loadDialog;
    Option * _option;
    Information * _information;
    QString _saveName;
    QString _loadName;


    int _gridSize = 0;
    int _indicatorSize = 0;
    QSettings * _save;

    PawnDesign _pawnDesign = PawnDesign::BrightSquare;
    PawnDesign _newPawnDesign = PawnDesign::BrightSquare;


    Qt::CheckState _needHelpIncorrectInRowColumn = Qt::CheckState::Checked;
    Qt::CheckState _newHelpIncorrectInRowColumn = Qt::CheckState::Checked;

    Qt::CheckState _needHelpUnbalancedRowColumn = Qt::CheckState::Unchecked;
    Qt::CheckState _newHelpUnbalancedRowColumn = Qt::CheckState::Unchecked;

    Qt::CheckState _needHelpIdenticalRowColunm = Qt::CheckState::Unchecked;
    Qt::CheckState _newHelpIdenticalRowColunm = Qt::CheckState::Unchecked;


    Qt::CheckState _needHelpIndicator = Qt::CheckState::Checked;
    Qt::CheckState _newHelpIndicator = Qt::CheckState::Checked;


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
    void onHelpIndicator(Qt::CheckState state);
    void onHelpIncorrectInRowColumn(Qt::CheckState state);
    void onHelpUnbalancedRowColumn(Qt::CheckState state);
    void onHelpIdenticalRowColumn(Qt::CheckState state);


signals:
    void pawnChanged(const int & id, const State & state);
};

#endif
