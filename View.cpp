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

    connect(ui->actionNew,SIGNAL(triggered(bool)),this,SLOT(pressedNew(bool)));

}

View::~View()
{
    delete _chronometer;
    delete _time;
    delete ui;
}

QGridLayout* View::loadPawnsOnGrid(const int & size,Pawn * pawns)
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

QGridLayout *View::loadPawnsOnGrid(const int &size, Pawn *pawns, Indicator *indicator)
{
    QGridLayout *gridLayout = new QGridLayout;

    for (int row = 0; row < size; row++) {
        for (int column = 0; column <size; column++) {
            gridLayout->addWidget(&pawns[ row * size + column],row,column);
        }
        gridLayout->addWidget(&indicator[row],row,size);
        gridLayout->addWidget(&indicator[row+size],size,row);

        indicator[row].updateData();
        indicator[row+size].updateData();

    }
    gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    return gridLayout;
}

void View::loadUi(const int &size, Pawn *pawns)
{

    QHBoxLayout *mainLayout = new QHBoxLayout;
    QGridLayout *leftLayout = loadPawnsOnGrid(size,pawns);
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

void View::loadUi(const int &size, Pawn *pawns, Indicator *indicator)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QGridLayout *leftLayout = loadPawnsOnGrid(size,pawns,indicator);
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

    _metronome = new QTimer(this);
    _metronome->setInterval(1000);

    connect(_metronome,SIGNAL(timeout()),this,SLOT(onTimerTimeout()));


    _metronome->start();
    _time->start();
}

void View::loadTestPawn()
{
    int size = 9;
    Pawn *visualPawns = new Pawn[size];
    for (int i = 0;i < size;i++) {
        visualPawns[i].setMinimumSize(64,64);
        visualPawns[i].changeDesignWith(new Pawn::BrightSquare);
    }
    visualPawns[1].setState(White);
    visualPawns[2].setState(White);
    visualPawns[2].setFalse(true);
    visualPawns[3].setState(White);
    visualPawns[3].setLock(true);
    visualPawns[4].setState(White);
    visualPawns[4].setFalse(true);
    visualPawns[4].setLock(true);

    visualPawns[5].setState(Black);
    visualPawns[6].setState(Black);
    visualPawns[6].setFalse(true);
    visualPawns[7].setState(Black);
    visualPawns[7].setLock(true);
    visualPawns[8].setState(Black);
    visualPawns[8].setFalse(true);
    visualPawns[8].setLock(true);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(&visualPawns[0],0,0);
    for (int i =1;i< size;i++) {
        mainLayout->addWidget(&visualPawns[i],1+i/(size/2+1),i%(size/2));
    }
    Indicator *indicator = new Indicator(0,nullptr);
    indicator->setMinimumSize(40,40);
    mainLayout->addWidget(indicator,3,0);
    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    ui->centralWidget->setLayout(mainLayout);
}

void View::stopMetronome()
{
    _metronome->setInterval(0);
}

void View::startMetronome()
{
    _metronome->setInterval(1000);
}

QString View::getChronometerTime(){
    QString timer = "";
    timer += QString::number(_chronometer->time().hour())+"-";
    timer += QString::number(_chronometer->time().minute())+"-";
    timer += QString::number(_chronometer->time().second())+"-";
    return timer;
}

void View::setChronometerTo(int hour, int min, int s)
{
    _chronometer->time().setHMS(hour,min,s);
}

void View::onTimerTimeout()
{
    _chronometer->setTime(_chronometer->time().addMSecs(_time->restart()));
}

void View::pressedNew (bool check)
{
    emit sendPressedNew();
}
