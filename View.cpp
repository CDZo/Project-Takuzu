#include "presenter.h"
#include "ui_vue.h"
#include <QIcon>
#include <QLineEdit>
#include <QTextStream>
#include <QRandomGenerator>
#include <QIODevice>

presenter::presenter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::presenter)
{
    _model = new ModelTakuzu(this);
    _model->initGrid(6);

    ui->setupUi(this);

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(new Pawn(),0,0);
    ui->centralWidget->setLayout(gridLayout);
}

presenter::~presenter()
{
    delete ui;
}

void presenter::createGrid(int size, int difficulty){
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
