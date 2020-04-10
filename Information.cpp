#include "Information.h"
#include "ui_Information.h"

Information::Information(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Information)
{
    ui->setupUi(this);
}

Information::~Information()
{
    delete ui;
}

void Information::setInformationTextWith(const QString &information)
{
    ui->informationHolder->setText(information);
}
