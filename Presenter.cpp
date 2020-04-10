#include "Presenter.h"
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QChar>
#include <QtMath>
#include <QTime>
#include <time.h>

Presenter::Presenter()
{
    initViews();

    initNewGrid(6,Easy);
    //_newGame->setModal(true);

    initConnectionWithModel();
    initConnectionWithViews();

}


Presenter::~Presenter()
{
    delete[] _visualPawns;
    delete _model;
    delete [] _indicators;
    delete _view;
    delete _error;
    delete _newGame;
    delete _saveDialog;
    delete _loadDialog;
    delete _option;
}

Pawn * Presenter::initVisualPawnWith(const int & gridSize,const Difficulty & difficulty)
{
    Pawn * pawnGrid = new Pawn[gridSize * gridSize];
    QString filePath = ":/grid/";
    filePath += QString::number(gridSize);
    switch (difficulty){
    case Easy:
        filePath += "_easy.txt";
        break;
    case Hard:
        filePath += "_hard.txt";
        break;
    }
    //std::cout<<filePath.toStdString()<<std::endl<<std::flush;

    QString grid = "";

    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly)){
        QTextStream text(&file);
        int i = text.readLine().toInt();
        QRandomGenerator rand;
        rand.seed(time(NULL));
        i = rand.bounded(1,i+1);
        for (int k = 0;k < i;k++) {
            grid=text.readLine();
        }

        const QChar* data=grid.constData();

        for(int k = 0; k < grid.length();k++){
            if (data[k] == "."){
                pawnGrid[k].setLock(false);
                pawnGrid[k].setState(Empty);
            }
            else if (data[k] == "B"){
                pawnGrid[k].setLock(true);
                pawnGrid[k].setState(Black);
            }
            else if (data[k] == "W"){
                pawnGrid[k].setLock(true);
                pawnGrid[k].setState(White);
            }

        }
        //std::cout<<_gridSize<<std::endl<<std::flush;
        //std::cout<<grid.toStdString()<<std::endl<<std::flush;
        file.close();
        return pawnGrid;
    }
    else {
        std::cout<<"Error opening file"<<std::endl<<std::flush;
        return pawnGrid;
    }

}

void Presenter::saveGrid(QString name)
{
    QString grid = "";
    grid+= QString::number(_gridSize);
    grid += "-";
    for (int k=0;k<_gridSize*_gridSize;k++){
        grid+=_visualPawns[k].getCompleteState();
    }
    _save->setValue(name,grid);
    _save->setValue(name+"_timer",_view->getChronometerTime());
}

void Presenter::loadSavedGame(QString name)
{
    if (_save->value(name,0)!=0){
        std::cout << "old gridSize :"<< _gridSize<< std::endl <<std::flush;
        Pawn * pawns = loadSavedGrid(name);
        std::cout << "new gridSize :"<< _gridSize<< std::endl <<std::flush;
        replaceGrid(_gridSize,pawns);
        changeTimerWithSavedTimer(name);
    }
    else {
        _error->exec();
    }
}

void Presenter::show()
{
    _view->show();
}

void Presenter::resetFalsePawns()
{
    for(int i = 0; i< _gridSize*_gridSize;i++) {
        _visualPawns[i].setFalse(false);
    }
    _view->update();
}

void Presenter::initConnectionWithModel()
{
    connect(this,SIGNAL(pawnChanged(int, State)),_model,SLOT(onPawnChanged(int, State)));
    connect(_model,SIGNAL(incorrectPawnsInRow(std::set<std::pair<int,int>>)),this,SLOT(onIncorrectPawnsInRow(std::set<std::pair<int,int>>)));
    connect(_model,SIGNAL(incorrectPawnsInColumn(std::set<std::pair<int,int>>)),this,SLOT(onIncorrectPawnsInColumn(std::set<std::pair<int,int>>)));
    connect(_model,SIGNAL(unbalancedRows(std::set<int>)),this,SLOT(onUnbalancedRows(std::set<int>)));
    connect(_model,SIGNAL(unbalancedColumns(std::set<int>)),this,SLOT(onUnbalancedColumns(std::set<int>)));
    connect(_model,SIGNAL(identicalRows(std::set<std::pair<int,int>>)),this,SLOT(onIdenticalRows(std::set<std::pair<int,int>>)));
    connect(_model,SIGNAL(identicalColumns(std::set<std::pair<int,int>>)),this,SLOT(onIdenticalColumns(std::set<std::pair<int,int>>)));
    connect(_model,SIGNAL(notify()),this,SLOT(onGameFinished()));
}

void Presenter::initNewGrid(const int &size, const Difficulty &difficulty)
{
    _gridSize = size;
    _indicatorSize = 2* _gridSize;
    _visualPawns = initVisualPawnWith(_gridSize,difficulty);
    _indicators = initNewIndicator(_gridSize);

    _model = new ModelTakuzu(this);
    _model->initGrid(_gridSize,_visualPawns);

    for(int i = 0; i < _indicatorSize;i++) {
        _indicators[i].setSubject(_model);
        _model->addObserver(&_indicators[i]);
        _indicators[i].setMinimumSize(45,45);
    }

    for(int i = 0; i < _gridSize*_gridSize;i++) {
        _visualPawns[i].setMinimumSize(45,45);
        _visualPawns[i].changeDesignWith(new Pawn::BrightSquare);
        //_visualPawns[i].setFixedSize(32,32);
        connect(&_visualPawns[i],SIGNAL(onClicked(int,State)),this,SLOT(onPawnClicked(int, State)));
        _visualPawns[i].setId(i);
    }

    _view->loadUi(_gridSize,_visualPawns,_indicators);
}

Indicator * Presenter::initNewIndicator(const int &gridSize)
{
    Indicator * indicators = new Indicator[gridSize*gridSize];
    for(int i = 0; i < _gridSize;i++) {
        indicators[i].setPosition(i);
        indicators[i+_gridSize].setOrientation(Vertical);
        indicators[i+_gridSize].setPosition(i);
    }
    return indicators;
}


void Presenter::replaceWithNewGrid(const int &size, const Difficulty &difficulty)
{
    _gridSize = size;
    _indicatorSize = 2* _gridSize;
    /*TODO check memory leak*/
    delete [] _visualPawns;
    delete [] _indicators;
    _visualPawns = initVisualPawnWith(_gridSize,difficulty);
    _indicators = initNewIndicator(_gridSize);
    _model->replaceGrid(_gridSize,_visualPawns);

    for(int i = 0; i < _indicatorSize;i++) {
        _indicators[i].setSubject(_model);
        _model->addObserver(&_indicators[i]);
        _indicators[i].setMinimumSize(45,45);
    }
    for(int i = 0; i < _gridSize*_gridSize;i++) {
        _visualPawns[i].setMinimumSize(45,45);
        _visualPawns[i].changeDesignWith(new Pawn::BrightSquare);
        //_visualPawns[i].setFixedSize(32,32);
        connect(&_visualPawns[i],SIGNAL(onClicked(int,State)),this,SLOT(onPawnClicked(int, State)));
        _visualPawns[i].setId(i);
    }
    _view->reloadUi(_gridSize,_visualPawns,_indicators);
}

void Presenter::replaceGrid(const int &size, Pawn *pawns)
{
    _gridSize = size;
    _indicatorSize = 2* _gridSize;
    /*TODO check memory leak*/
    delete [] _visualPawns;
    delete [] _indicators;
    _visualPawns = pawns;
    _indicators = initNewIndicator(_gridSize);
    _model->replaceGrid(_gridSize,_visualPawns);

    for(int i = 0; i < _indicatorSize;i++) {
        _indicators[i].setSubject(_model);
        _model->addObserver(&_indicators[i]);
        _indicators[i].setMinimumSize(45,45);
    }
    for(int i = 0; i < _gridSize*_gridSize;i++) {
        _visualPawns[i].setMinimumSize(45,45);
        _visualPawns[i].changeDesignWith(new Pawn::BrightSquare);
        //_visualPawns[i].setFixedSize(32,32);
        connect(&_visualPawns[i],SIGNAL(onClicked(int,State)),this,SLOT(onPawnClicked(int, State)));
        _visualPawns[i].setId(i);
    }
    _view->reloadUi(_gridSize,_visualPawns,_indicators);
}



Pawn *Presenter::loadSavedGrid(QString name)
{
    QString grid = _save->value(name,0).toString();
    QString gridSize = "";
    int k=0;
    const QChar* data=grid.constData();
    while(data[k]!="-"){
        gridSize += data[k];
        k++;
    }
    k++;
    _gridSize=gridSize.toInt();
    Pawn * pawnGrid = new Pawn[_gridSize*_gridSize];
    int pawnId=0;
    for (int i=k;i<(_gridSize*_gridSize*2)+k;i+=2){

        if (data[i]=="."){
            pawnGrid[pawnId].setState(Empty);
        }
        else if (data[i]=="B"){
            pawnGrid[pawnId].setState(Black);
        }
        else if (data[i]=="W"){
            pawnGrid[pawnId].setState(White);
        }

        if (data[i+1]=="0"){
            pawnGrid[pawnId].setLock(false);
        }
        else if (data[i+1]=="1"){
            pawnGrid[pawnId].setLock(true);
        }
        pawnGrid[pawnId].setId(pawnId);
        pawnId++;
    }
    return pawnGrid;
}

void Presenter::changeTimerWithSavedTimer(QString name)
{
    int hour,min,sec;
    QString time = _save->value(name+"_timer",0).toString();

    const QChar* timer_data=time.constData();

    int k=0;

    QString timer = "";
    while(timer_data[k]!="-"){
        timer += timer_data[k];
        k++;
    }
    k++;
    hour=timer.toInt();

    timer = "";
    while(timer_data[k]!="-"){
        timer += timer_data[k];
        k++;
    }
    k++;
    min=timer.toInt();

    timer = "";
    while(timer_data[k]!="-"){
        timer += timer_data[k];
        k++;
    }
    k++;
    sec=timer.toInt();
    _view->setChronometerTo(hour,min,sec);
}

void Presenter::initViews()
{
    _view = new View;

    _save = new QSettings;

    _newGame = new NewGame;

    _saveDialog = new Save;

    _loadDialog = new Load;

    _error = new Error;

    _option = new Option;
}

void Presenter::initConnectionWithViews()
{
    connect(_view,SIGNAL(newPressed()),this,SLOT(onPressedNew()));
    connect(_view,SIGNAL(savePressed()),this,SLOT(onPressedSave()));
    connect(_view,SIGNAL(loadPressed()),this,SLOT(onPressedLoad()));
    connect(_view,SIGNAL(optionPressed()),this,SLOT(onPressedOption()));

    connect(_newGame,SIGNAL(sendSizeIndex(int)),this,SLOT(onReceivingNewSize(int)));
    connect(_newGame,SIGNAL(sendDifficultyIndex(int)),this,SLOT(onReceivingNewDifficulty(int)));

    connect(_saveDialog,SIGNAL(saveNameChanged(QString)),this,SLOT(onReceivingSaveName(QString)));

    connect(_loadDialog,SIGNAL(loadNameChanged(QString)),this,SLOT(onReceivingLoadName(QString)));

    connect(_option,SIGNAL(helpIncorrectInRowColumn(Qt::CheckState)),this,SLOT(onHelpIncorrectInRowColumn(Qt::CheckState)));
    connect(_option,SIGNAL(helpUnbalancedRowColumn(Qt::CheckState)),this,SLOT(onHelpUnbalancedRowColumn(Qt::CheckState)));
    connect(_option,SIGNAL(helpIdenticalRowColumn(Qt::CheckState)),this,SLOT(onHelpIdenticalRowColumn(Qt::CheckState)));

}

void Presenter::setIncorrectRowPawnWith(const bool &value, const std::set<std::pair<int, int> > &pawns)
{
    for(std::set<std::pair<int, int>>::iterator it = pawns.begin();it != pawns.end();it++) {
        _visualPawns[it->first * _gridSize + it->second].setFalse(value);
    }
}

void Presenter::setIncorrectColumnPawnWith(const bool &value, const std::set<std::pair<int, int> > &pawns)
{
    for(std::set<std::pair<int, int>>::iterator it = pawns.begin();it != pawns.end();it++) {
        _visualPawns[it->first * _gridSize + it->second].setFalse(value);
    }
}

void Presenter::setColumnWith(const bool &value, std::set<int> columns)
{
    for(std::set<int>::iterator it = columns.begin();it != columns.end();it++) {
        for(int row = 0; row < _gridSize; row++) {
            _visualPawns[row * _gridSize + *it].setFalse(value);
        }
    }
}

void Presenter::setRowWith(const bool &value, std::set<int> rows)
{
    for(std::set<int>::iterator it = rows.begin();it != rows.end();it++) {
        for(int column = 0; column < _gridSize; column++) {
            _visualPawns[*it * _gridSize + column].setFalse(value);
        }
    }
}



void Presenter::onPawnClicked(const int & id, const State & state)
{
    resetFalsePawns();
    _view->setStatusBarTextWith(tr(""));
    emit pawnChanged(id, state);
}

void Presenter::onIncorrectPawnsInRow(const std::set<std::pair<int, int>> pawns)
{
    if(_needHelpIncorrectInRowColumn) {
        setIncorrectRowPawnWith(true,pawns);
        _view->update();
    }
}

void Presenter::onIncorrectPawnsInColumn(const std::set<std::pair<int, int>> pawns)
{
    if (_needHelpIncorrectInRowColumn) {
        setIncorrectColumnPawnWith(true,pawns);
        _view->update();
    }
}

void Presenter::onUnbalancedRows(std::set<int> rows)
{
    if (_needHelpUnbalancedRowColumn) {
        setRowWith(true,rows);
        _view->setStatusBarTextWith(tr("unbalanced row/column"));
        _view->update();
    }
}

void Presenter::onUnbalancedColumns(std::set<int> columns)
{

    if (_needHelpUnbalancedRowColumn) {
        setColumnWith(true,columns);
        _view->setStatusBarTextWith(tr("unbalanced row/column"));
        _view->update();
    }

}


void Presenter::onIdenticalRows(std::set<std::pair<int, int> > rows)
{
    std::set<int> singleRows;
    for(std::set<std::pair<int,int>>::iterator it = rows.begin();it != rows.end();it++) {
        singleRows.insert(it->first);
        singleRows.insert(it->second);
    }
    if(_needHelpIdenticalRowColunm) {
        setRowWith(true,singleRows);
        _view->setStatusBarTextWith(tr("identical rows/columns"));
        _view->update();
    }
}

void Presenter::onIdenticalColumns(std::set<std::pair<int, int> > columns)
{
    std::set<int> singleColumns;
    for(std::set<std::pair<int,int>>::iterator it = columns.begin();it != columns.end();it++) {
        singleColumns.insert(it->first);
        singleColumns.insert(it->second);
    }

    if(_needHelpIdenticalRowColunm == Qt::CheckState::Checked) {
        setColumnWith(true,singleColumns);
        _view->setStatusBarTextWith(tr("identical rows/columns"));
        _view->update();
    }
}

void Presenter::onGameFinished()
{
    for(int i =0; i< _gridSize*_gridSize;i++) {
        _visualPawns[i].setLock(true);
    }

    _view->stopMetronome();
    _view->update();
    _view->setStatusBarTextWith(tr("You Won !! (＾▽＾)"));

}




void Presenter::onReceivingNewSize(int index){
    switch (index){
    case 0:
        _newSize=6;
        break;
    case 1:
        _newSize=8;
        break;
    case 2:
        _newSize=10;
        break;
    }
}
void Presenter::onReceivingNewDifficulty(int index){
    switch (index){
    case 0:
        _newDifficulty=Easy;
        break;
    case 1:
        _newDifficulty=Hard;
        break;
    }
}

void Presenter::onPressedNew() {
    int playerNeedNewGrid = _newGame->exec();
    if(playerNeedNewGrid) {
        replaceWithNewGrid(_newSize,_newDifficulty);
        _view->setStatusBarTextWith("");
    }
}

void Presenter::onPressedOption()
{
    int playerWantOption = _option->exec();
    if (playerWantOption) {
        _needHelpIncorrectInRowColumn = _newHelpIncorrectInRowColumn;
        _needHelpUnbalancedRowColumn = _newHelpUnbalancedRowColumn;
        _needHelpIdenticalRowColunm = _newHelpIdenticalRowColunm;
        resetFalsePawns();
        _model->rulesLoop();
    }
}

void Presenter::onHelpIncorrectInRowColumn(Qt::CheckState state)
{
    _newHelpIncorrectInRowColumn = state;
    std::cout<<"onHelpIncorrectInRowColumn :"<< state <<std::endl<<std::flush;
}

void Presenter::onHelpUnbalancedRowColumn(Qt::CheckState state)
{
    _newHelpUnbalancedRowColumn = state;
    std::cout<<"onHelpUnbalancedRowColumn :"<< state <<std::endl<<std::flush;
}

void Presenter::onHelpIdenticalRowColumn(Qt::CheckState state)
{
    _newHelpIdenticalRowColunm = state;
    std::cout<<"onHelpIdenticalRowColumn :"<< state <<std::endl<<std::flush;
}


void Presenter::onPressedSave() {
    int playerNeedSave = _saveDialog->exec();
    if(playerNeedSave) {
        saveGrid(_saveName);
    }
    std::cout<<"code retrieve after execution :"<< playerNeedSave<<std::endl<<std::flush;
}

void Presenter::onPressedLoad() {
    int playerNeedLoad = _loadDialog->exec();
    if(playerNeedLoad) {
        loadSavedGame(_loadName);
    }
    std::cout<<"code retrieve after execution :"<< playerNeedLoad<<std::endl<<std::flush;
}

void Presenter::onReceivingSaveName(QString text){
    _saveName=text;
    std::cout<<std::endl<<std::endl<<"Save >>"+text.toStdString()<<"<<"<<std::endl<<std::endl<<std::flush;
}

void Presenter::onReceivingLoadName(QString text){
    _loadName=text;
    std::cout<<std::endl<<std::endl<<"Load >>"+text.toStdString()<<"<<"<<std::endl<<std::endl<<std::flush;
}
