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
    _size = 6;
    _model = new ModelTakuzu;
    _model->initGrid(_size);
    _visualPawns = new Pawn[_size*_size];
    _view = new View;
    createGrid(0);
}

Presenter::~Presenter()
{
    delete[] _visualPawns;
    delete _view;
}

void Presenter::createGrid(const int &difficulty)
{
    QString filePath = ":/grid/";
    filePath += QString::number(_size);
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
        rand.seed(time(NULL));
        i = rand.bounded(1,i+1);
        for (int k=0;k<i;k++) {
            grid=text.readLine();
        }

        const QChar* data=grid.constData();

        for(int k=0;k<grid.length();k++){
            QChar character = data[k];
            if (data[k]=="."){
                _visualPawns[k].setLock(false);
                _visualPawns[k].setState(Empty);
            }
            else if (data[k]=="B"){
                _visualPawns[k].setLock(true);
                _visualPawns[k].setState(Black);
            }
            else if (data[k]=="W"){
                _visualPawns[k].setLock(true);
                _visualPawns[k].setState(White);
            }

        }
        _view->loadPawnsOnGrid(_visualPawns,_size);
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
