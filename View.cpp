#include "View.h"
#include "ui_vue.h"
#include <QIcon>
#include <QLineEdit>
#include <QTextStream>
#include <QRandomGenerator>
#include <QIODevice>
#include <QPushButton>
#include <QTimer>

View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);

    ui->actionNew->setIcon(QIcon::fromTheme("document-new"));
    ui->actionOpen->setIcon(QIcon::fromTheme("document-open"));
    ui->actionSave->setIcon(QIcon::fromTheme("document-save"));
    ui->statusBar->showMessage("status bar here");
    QPushButton rightButton("button",this);
    rightButton.setGeometry(10,10,100,100);

}

View::~View()
{
    delete ui;
}

QGridLayout* View::loadPawnsOnGrid(Pawn * pawns, const int & size)
{

    QGridLayout *gridLayout = new QGridLayout;

    for (int row = 0; row < size; row++) {
        for (int column = 0; column <size; column++) {
            gridLayout->addWidget(&pawns[ row * size + column],row,column);
        }
    }
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    return gridLayout;
}

void View::loadUi(Pawn *pawns, const int &size)
{

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QGridLayout *leftLayout = loadPawnsOnGrid(pawns,size);
    //leftLayout->setSizeConstraint(QLayout::SetMinimumSize);
    mainLayout->addLayout(leftLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(rightLayout);

    _chronometer = new QTimeEdit;
    _chronometer->setDisplayFormat("mm: ss");
    _chronometer->setReadOnly(true);
    rightLayout->addWidget(_chronometer);
    rightLayout->setSizeConstraint(QLayout::SetMinimumSize);

    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setStretch(0,1);
    ui->centralWidget->setLayout(mainLayout);

    _time = new QElapsedTimer;

    QTimer * timerChronometer = new QTimer(this);
    timerChronometer->setInterval(1000);

    connect(timerChronometer,SIGNAL(timeout()),this,SLOT(onTimerTimeout()));


    timerChronometer->start();
    _time->start();
}

void View::loadTestPawn(Pawn *pawn, const int & size)
{

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(&pawn[0],0,0);
    for (int i =1;i< size;i++) {
        mainLayout->addWidget(&pawn[i],1+i/(size/2+1),i%(size/2));
    }
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    ui->centralWidget->setLayout(mainLayout);
}

void View::onTimerTimeout()
{
    _chronometer->setTime(_chronometer->time().addMSecs(_time->restart()));
}
