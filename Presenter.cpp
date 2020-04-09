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
    initNewGrid(6,Easy);
    //_newGame->setModal(true);

    initConnectionWithModel();

    _newGame = new NewGame;

    _saveDialog = new Save;

    _loadDialog = new Load;


    connect(_newGame,SIGNAL(sendSizeIndex(int)),this,SLOT(onReceivingNewSize(int)));
    connect(_newGame,SIGNAL(sendDifficultyIndex(int)),this,SLOT(onReceivingNewDifficulty(int)));

    connect(_saveDialog,SIGNAL(sendText(QString)),this,SLOT(onReceivingSaveName(QString)));

    connect(_loadDialog,SIGNAL(sendText(QString)),this,SLOT(onReceivingLoadName(QString)));

    connect(_view,SIGNAL(sendPressedNew()),this,SLOT(onPressedNew()));
    connect(_view,SIGNAL(sendPressedSave()),this,SLOT(onPressedSave()));
    connect(_view,SIGNAL(sendPressedLoad()),this,SLOT(onPressedLoad()));





}


Presenter::~Presenter()
{
    delete[] _visualPawns;
    delete _model;
    delete [] _indicators;
    delete _view;
    delete _newGame;
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
    _save.setValue(name,grid);
    _save.setValue(name+"_timer",_view->getChronometerTime());
}

void Presenter::loadSavedGrid(QString name)
{
    QString grid = _save.value(name,0).toString();
    QString time = _save.value(name+"_timer",0).toString();
    QString gridSize = "";
    int k=0;
    const QChar* data=grid.constData();
    while(data[k]!="-"){
        gridSize += data[k];
        k++;
    }
    k++;
    _gridSize=gridSize.toInt();
    int pawnId=0;
    for (int i=k;i<(_gridSize*_gridSize*2)+k;i+=2){

        if (data[i]=="."){
            _visualPawns[pawnId].setState(Empty);
        }
        else if (data[i]=="B"){
            _visualPawns[pawnId].setState(Black);
        }
        else if (data[i]=="W"){
            _visualPawns[pawnId].setState(White);
        }



        if (data[i+1]=="0"){
            _visualPawns[pawnId].setLock(false);
        }
        else if (data[i+1]=="1"){
            _visualPawns[pawnId].setLock(true);
        }
        _visualPawns[pawnId].setId(pawnId);
        pawnId++;
    }

    int hour,min,sec;

    const QChar* timer_data=time.constData();

    k=0;

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
    _view = new View;
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

void Presenter::replaceGrid(const int &size, const Difficulty &difficulty)
{
    _gridSize = size;
    _indicatorSize = 2* _gridSize;
    _visualPawns = initVisualPawnWith(_gridSize,difficulty);
    _indicators = initNewIndicator(_gridSize);


}



void Presenter::onPawnClicked(const int & id, const State & state)
{
    //std::cout << "id: "<<id<<" state : "<<state <<std::endl;
    resetFalsePawns();
    emit pawnChanged(id, state);
}

void Presenter::onIncorrectPawnsInRow(const std::set<std::pair<int, int>> pawns)
{
    //std::cout<<"Incorrect Pawn in Row :"<<std::endl;
    for(std::set<std::pair<int, int>>::iterator it = pawns.begin();it != pawns.end();it++) {
        _visualPawns[it->first * _gridSize + it->second].setFalse(true);
        //std::cout << "x: " << it->first << " y : " << it->second <<std::endl;
    }
    _view->update();
}

void Presenter::onIncorrectPawnsInColumn(const std::set<std::pair<int, int> > pawns)
{
    //std::cout<<"Incorrect Pawn in Column :"<<std::endl;
    for(std::set<std::pair<int, int>>::iterator it = pawns.begin();it != pawns.end();it++) {
        _visualPawns[it->first * _gridSize + it->second].setFalse(true);
        //std::cout << "x: " << it->first << " y : " << it->second <<std::endl;
    }
    _view->update();
}

void Presenter::onUnbalancedRows(std::set<int> rows)
{
    for(std::set<int>::iterator it = rows.begin();it != rows.end();it++) {
        // std::cout << "unbalanced row: " << *it <<std::endl;
    }
    //std::cout<<std::endl;
}

void Presenter::onUnbalancedColumns(std::set<int> columns)
{
    for(std::set<int>::iterator it = columns.begin();it != columns.end();it++) {
        // std::cout << "unbalanced columns: " << *it <<std::endl;
    }
    //std::cout<<std::endl;
}

void Presenter::onIdenticalRows(std::set<std::pair<int, int> > rows)
{
    //std::cout<<"Identical Rows :"<<std::endl;
    for(std::set<std::pair<int,int>>::iterator it = rows.begin();it != rows.end();it++) {
        // std::cout << it->first <<" - " <<it->second <<std::endl;
    }
}

void Presenter::onIdenticalColumns(std::set<std::pair<int, int> > columns)
{
    // std::cout<<"Identical columns :"<<std::endl;
    for(std::set<std::pair<int,int>>::iterator it = columns.begin();it != columns.end();it++) {
        //  std::cout << it->first <<" - " <<it->second <<std::endl;
    }
}

void Presenter::onGameFinished()
{
    for(int i =0; i< _gridSize*_gridSize;i++) {
        _visualPawns[i].setLock(true);
    }
    _view->stopMetronome();
    _view->update();
    std::cout<<"You Won !!"<<std::endl;

}




void Presenter::onReceivingNewSize(int index){
    std::cout<<"size"<<std::flush;
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
    std::cout<<"diff"<<std::flush;
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
        initNewGrid(_newSize,_newDifficulty);
    }
    std::cout<<"code retrieve after execution :"<< playerNeedNewGrid<<std::endl<<std::flush;
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
        loadSavedGrid(_loadName);
    }
    std::cout<<"code retrieve after execution :"<< playerNeedLoad<<std::endl<<std::flush;
}

void Presenter::onReceivingSaveName(QString text){
    _saveName=text;
    std::cout<<std::endl<<std::endl<<"Save "+text.toStdString()<<std::endl<<std::endl<<std::flush;
}

void Presenter::onReceivingLoadName(QString text){
    _loadName=text;
    std::cout<<std::endl<<std::endl<<"Load "+text.toStdString()<<std::endl<<std::endl<<std::flush;
}
