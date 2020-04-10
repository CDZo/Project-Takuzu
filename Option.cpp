#include "Option.h"
#include "ui_Option.h"

Option::Option(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Option)
{
    ui->setupUi(this);
    connect(ui->comboDesign,SIGNAL(currentIndexChanged(int)),this,SLOT(onDesignChanged(int)));
    connect(ui->checkIncorrectInRowColumn,SIGNAL(stateChanged(int)),this,SLOT(onIncorrectInRowColumn(int)));
    connect(ui->checkUnbalancedRowColumn,SIGNAL(stateChanged(int)),this,SLOT(onUnbalancedRowColumn(int)));
    connect(ui->checkIdenticalRowColumn,SIGNAL(stateChanged(int)),this,SLOT(onIdenticalRowColumn(int)));
    connect(ui->checkIndicator,SIGNAL(stateChanged(int)),this,SLOT(onIndicatorChanged(int)));
    QStringList listDesign;

    listDesign.insert(PawnDesign::BrightCircle,tr("cercle clair"));
    listDesign.insert(PawnDesign::BrightSquare,tr("carré clair"));
    listDesign.insert(PawnDesign::DarkCircle,tr("cercle foncé"));
    listDesign.insert(PawnDesign::DarkSquare,tr("carré foncé"));

    ui->comboDesign->addItems(listDesign);
    ui->optionPawn->setState(State::Black);
}

Option::~Option()
{
    delete ui;
}

void Option::onDesignChanged(int design)
{
    ui->optionPawn->changeDesignWith(PawnDesign(design));
    emit pawnDesignChanged(PawnDesign(design));
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

void Option::onIndicatorChanged(int state)
{
    emit helpIndicator(Qt::CheckState(state));
}
