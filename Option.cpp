#include "Option.h"
#include "ui_Option.h"

Option::Option(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Option)
{
    ui->setupUi(this);
    connect(ui->checkIncorrectInRowColumn,SIGNAL(stateChanged(int)),this,SLOT(onIncorrectInRowColumn(int)));
    connect(ui->checkUnbalancedRowColumn,SIGNAL(stateChanged(int)),this,SLOT(onUnbalancedRowColumn(int)));
    connect(ui->checkIdenticalRowColumn,SIGNAL(stateChanged(int)),this,SLOT(onIdenticalRowColumn(int)));


}

Option::~Option()
{
    delete ui;
}

void Option::onIncorrectInRowColumn(int state)
{
    emit helpIncorrectInRowColumn(Qt::CheckState(state));
}

void Option::onUnbalancedRowColumn(int state)
{
    emit helpUnbalancedRowColumn(Qt::CheckState(state));
}

void Option::onIdenticalRowColumn(int state)
{
    emit helpIdenticalRowColumn(Qt::CheckState(state));
}
