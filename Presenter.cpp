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
    _gridSize = 10;
    _visualPawns = new Pawn[_gridSize*_gridSize];
    initVisualPawnWithDifficulty(Easy);

    _model = new ModelTakuzu;
    _model->initGrid(_gridSize,_visualPawns);
    //saveGrid("Test3");

    /*std::cout<<"----------Par ici !---------"<<std::endl<<std::endl<<_save.value("Test",0).toString().toStdString()<<std::endl<<std::endl<<std::flush;
    std::cout<<"----------Par ici !---------"<<std::endl<<std::endl<<_save.value("Test2",0).toString().toStdString()<<std::endl<<std::endl<<std::flush;
    std::cout<<"----------Par ici !---------"<<std::endl<<std::endl<<_save.value("Test3",0).toString().toStdString()<<std::endl<<std::endl<<std::flush;
    std::cout<<"----------Par ici !---------"<<std::endl<<std::endl<<_save.value("Test4",0).toString().toStdString()<<std::endl<<std::endl<<std::flush;

    loadSavedGrid("Test");
    loadSavedGrid("Test2");
    loadSavedGrid("Test3");
    loadSavedGrid("Test4");
*/

    for(int i = 0; i < _gridSize*_gridSize;i++) {
        _visualPawns[i].setMinimumSize(45,45);
        _visualPawns[i].changeDesignWith(new Pawn::BrightSquare);
        //_visualPawns[i].setFixedSize(32,32);
        connect(&_visualPawns[i],SIGNAL(onClicked(int,State)),this,SLOT(onPawnClicked(int, State)));
        _visualPawns[i].setId(i);
    }
    _view = new View;

    _view->loadUi(_gridSize,_visualPawns);

    connect(this,SIGNAL(pawnChanged(int, State)),_model,SLOT(onPawnChanged(int, State)));
    connect(_model,SIGNAL(incorrectPawnsInRow(std::set<std::pair<int,int>>)),this,SLOT(onIncorrectPawnsInRow(std::set<std::pair<int,int>>)));
    connect(_model,SIGNAL(incorrectPawnsInColumn(std::set<std::pair<int,int>>)),this,SLOT(onIncorrectPawnsInColumn(std::set<std::pair<int,int>>)));
    connect(_model,SIGNAL(unbalancedRows(std::set<int>)),this,SLOT(onUnbalancedRows(std::set<int>)));
    connect(_model,SIGNAL(unbalancedColumns(std::set<int>)),this,SLOT(onUnbalancedColumns(std::set<int>)));
    connect(_model,SIGNAL(identicalRows(std::set<std::pair<int,int>>)),this,SLOT(onIdenticalRows(std::set<std::pair<int,int>>)));
    connect(_model,SIGNAL(identicalColumns(std::set<std::pair<int,int>>)),this,SLOT(onIdenticalColumns(std::set<std::pair<int,int>>)));
    connect(_model,SIGNAL(notify()),this,SLOT(onGameFinished()));
}


Presenter::~Presenter()
{
    delete[] _visualPawns;
    delete _view;
}

void Presenter::initVisualPawnWithDifficulty(const Difficulty & difficulty)
{
    QString filePath = ":/grid/";
    filePath += QString::number(_gridSize);
    switch (difficulty){
    case Easy:
        filePath += "_easy.txt";
        break;
    case Hard:
        filePath += "_hard.txt";
        break;
    }
    std::cout<<filePath.toStdString()<<std::endl<<std::flush;

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
                _visualPawns[k].setLock(false);
                _visualPawns[k].setState(Empty);
            }
            else if (data[k] == "B"){
                _visualPawns[k].setLock(true);
                _visualPawns[k].setState(Black);
            }
            else if (data[k] == "W"){
                _visualPawns[k].setLock(true);
                _visualPawns[k].setState(White);
            }

        }
        std::cout<<_gridSize<<std::endl<<std::flush;
        std::cout<<grid.toStdString()<<std::endl<<std::flush;
        file.close();
    }
    else {
        std::cout<<"Error opening file"<<std::endl<<std::flush;
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
}

void Presenter::loadSavedGrid(QString name)
{
    QString grid = _save.value(name,0).toString();
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


    grid = "";
    for (int k=0;k<_gridSize*_gridSize;k++){
        grid+=_visualPawns[k].getCompleteState();
    }
    std::cout<<"----------HEHO---------"<<std::endl<<std::endl<<grid.toStdString()<<std::endl<<std::endl<<std::flush;

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

void Presenter::onPawnClicked(const int & id, const State & state)
{
    //std::cout << "id: "<<id<<" state : "<<state <<std::endl;
    resetFalsePawns();
    emit pawnChanged(id, state);
}

void Presenter::onIncorrectPawnsInRow(const std::set<std::pair<int, int>> pawns)
{
    std::cout<<"Incorrect Pawn in Row :"<<std::endl;
    for(std::set<std::pair<int, int>>::iterator it = pawns.begin();it != pawns.end();it++) {
        _visualPawns[it->first * _gridSize + it->second].setFalse(true);
        std::cout << "x: " << it->first << " y : " << it->second <<std::endl;
    }
    _view->update();
}

void Presenter::onIncorrectPawnsInColumn(const std::set<std::pair<int, int> > pawns)
{
    std::cout<<"Incorrect Pawn in Column :"<<std::endl;
    for(std::set<std::pair<int, int>>::iterator it = pawns.begin();it != pawns.end();it++) {
        _visualPawns[it->first * _gridSize + it->second].setFalse(true);
        std::cout << "x: " << it->first << " y : " << it->second <<std::endl;
    }
    _view->update();
}

void Presenter::onUnbalancedRows(std::set<int> rows)
{
    for(std::set<int>::iterator it = rows.begin();it != rows.end();it++) {
        std::cout << "unbalanced row: " << *it <<std::endl;
    }
    std::cout<<std::endl;
}

void Presenter::onUnbalancedColumns(std::set<int> columns)
{
    for(std::set<int>::iterator it = columns.begin();it != columns.end();it++) {
        std::cout << "unbalanced columns: " << *it <<std::endl;
    }
    std::cout<<std::endl;
}

void Presenter::onIdenticalRows(std::set<std::pair<int, int> > rows)
{
    std::cout<<"Identical Rows :"<<std::endl;
    for(std::set<std::pair<int,int>>::iterator it = rows.begin();it != rows.end();it++) {
        std::cout << it->first <<" - " <<it->second <<std::endl;
    }
}

void Presenter::onIdenticalColumns(std::set<std::pair<int, int> > columns)
{
    std::cout<<"Identical columns :"<<std::endl;
    for(std::set<std::pair<int,int>>::iterator it = columns.begin();it != columns.end();it++) {
        std::cout << it->first <<" - " <<it->second <<std::endl;
    }
}

void Presenter::onGameFinished()
{
    for(int i =0; i< _gridSize*_gridSize;i++) {
        _visualPawns[i].setLock(true);
    }
    _view->update();
}

