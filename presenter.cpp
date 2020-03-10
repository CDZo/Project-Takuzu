#include "presenter.h"
#include "ui_vue.h"

presenter::presenter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::presenter)
{
    ui->setupUi(this);
}

presenter::~presenter()
{
    delete ui;
}
