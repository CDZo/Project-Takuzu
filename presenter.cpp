#include "presenter.h"
#include "ui_vue.h"

presenter::presenter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::presenter)
{
    ui->setupUi(this);
    std::cout <<"defaulty";
    std::cout << std::flush;
}

presenter::~presenter()
{
    delete ui;
}
