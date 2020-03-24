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
    connect(ui->toto,SIGNAL(onClicked(int,int,int)),_model,SLOT(onPawnChanged(int,int,int)));
}

presenter::~presenter()
{
    delete ui;
}
