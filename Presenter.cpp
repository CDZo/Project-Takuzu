#include "Presenter.h"
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
Presenter::Presenter()
{
    _size = 4;
    _model = new ModelTakuzu;
    _model->initGrid(_size);
    _visualPawns = new Pawn[_size*_size];

    _visualPawns[0].setState(Black);
    _visualPawns[0].setId(0);
    _visualPawns[1].setState(White);
    _visualPawns[1].setLock(true);

    _view = new View;
    _view->loadPawnsOnGrid(_visualPawns,_size);
    for(int i = 0; i < _size*_size;i++) {
        connect(&_visualPawns[i],SIGNAL(onClicked(int,State)),this,SLOT(onPawnClicked(int, State)));
        _visualPawns[i].setId(i);
    }
    connect(this,SIGNAL(pawnChanged(int, State)),_model,SLOT(onPawnChanged(int, State)));
}


Presenter::~Presenter()
{
    delete[] _visualPawns;
    delete _view;
}

void Presenter::createGrid(const int &size, const int &difficulty)
{
    QString filePath = ":/grid/";
    filePath += QString::number(size);
    switch (difficulty){
    case 0:
        filePath += "_easy.txt";
        break;
    case 1:
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
        i = rand.bounded(1,i+1);
        for (int k=0;k<i;k++) {
            grid=text.readLine();
        }
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

void Presenter::onPawnClicked(const int & id, const State & state)
{
    std::cout << "id: "<<id<<" state : "<<state <<std::endl;
    emit pawnChanged(id, state);
}
