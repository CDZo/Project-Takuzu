#include "Error.h"
#include "ui_Error.h"

Error::Error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Error)
{
    ui->setupUi(this);
}

Error::~Error()
{
    delete ui;
}
