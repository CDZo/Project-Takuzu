#include "presenter.h"
#include "ui_vue.h"
#include <QIcon>

presenter::presenter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::presenter)
{
    _model = new ModelTakuzu(this);
    _model->initGrid(6);

    ui->setupUi(this);
    ui->actionNew->setIcon(QIcon::fromTheme("document-new"));
    ui->actionOpen->setIcon(QIcon::fromTheme("document-open"));
    ui->actionSave->setIcon(QIcon::fromTheme("document-save"));
    ui->firstPawn->setPosition(0,0);
    ui->secondPawn->setPosition(0,1);

    ui->firstPawn->setLock(true);
    ui->firstPawn->setState(State::White);
    connect(ui->firstPawn,SIGNAL(onClicked(int,int,State)),_model,SLOT(onPawnChanged(int,int,State)));
    connect(ui->secondPawn,SIGNAL(onClicked(int,int,State)),_model,SLOT(onPawnChanged(int,int,State)));
}

presenter::~presenter()
{
    delete ui;
}
