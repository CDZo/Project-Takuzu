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
    int size = 9;
    _visualPawns = new Pawn[size];
    for (int i = 0;i < size;i++) {
        _visualPawns[i].setMinimumSize(64,64);
        _visualPawns[i].changeDesignWith(new Pawn::DarkCircle);
    }
    _visualPawns[1].setState(White);
    _visualPawns[2].setState(White);
    _visualPawns[2].setFalse(true);
    _visualPawns[3].setState(White);
    _visualPawns[3].setLock(true);
    _visualPawns[4].setState(White);
    _visualPawns[4].setFalse(true);
    _visualPawns[4].setLock(true);

    _visualPawns[5].setState(Black);
    _visualPawns[6].setState(Black);
    _visualPawns[6].setFalse(true);
    _visualPawns[7].setState(Black);
    _visualPawns[7].setLock(true);
    _visualPawns[8].setState(Black);
    _visualPawns[8].setFalse(true);
    _visualPawns[8].setLock(true);



    _view = new View;
    _view->loadTestPawn(_visualPawns,size);
}


Presenter::~Presenter()
{
    delete[] _visualPawns;
    delete _view;
}

void Presenter::initVisualPawnWithDifficulty(const Difficulty & difficulty)
{
    QString filePath = ":/grid/";
    filePath += QString::number(_size);
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
        std::cout<<_size<<std::endl<<std::flush;
        std::cout<<grid.toStdString()<<std::endl<<std::flush;
        file.close();
    }
    else {
        std::cout<<"Error opening file"<<std::endl<<std::flush;
    }

}

void Presenter::show()
{
    _view->show();
}

void Presenter::resetFalsePawns()
{
    for(int i = 0; i< _size*_size;i++) {
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
    for(std::set<std::pair<int, int>>::iterator it = pawns.begin();it != pawns.end();it++) {
        _visualPawns[it->first * _size + it->second].setFalse(true);
        //std::cout << "x: " << it->first << " y : " << it->second <<std::endl;
    }
    _view->update();
}

void Presenter::onIncorrectPawnsInColumn(const std::set<std::pair<int, int> > pawns)
{
    for(std::set<std::pair<int, int>>::iterator it = pawns.begin();it != pawns.end();it++) {
        _visualPawns[it->first * _size + it->second].setFalse(true);
        //std::cout << "x: " << it->first << " y : " << it->second <<std::endl;
    }
    _view->update();
}

void Presenter::onUnbalancedRows(std::set<int> rows)
{
    for(std::set<int>::iterator it = rows.begin();it != rows.end();it++) {
     //   std::cout << "unbalanced row: " << *it <<std::endl;
    }
    std::cout<<std::endl;
}

void Presenter::onUnbalancedColumns(std::set<int> columns)
{
    for(std::set<int>::iterator it = columns.begin();it != columns.end();it++) {
       // std::cout << "unbalanced columns: " << *it <<std::endl;
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

