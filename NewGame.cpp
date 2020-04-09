#include "NewGame.h"
#include "ui_NewGame.h"

NewGame::NewGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGame)
{
    ui->setupUi(this);
    connect(ui->sizeBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onSizeIndex(int)));
    connect(ui->difficultBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onDifficultyIndex(int)));
}

NewGame::~NewGame()
{
    delete ui;
}


void NewGame::onSizeIndex(int index){
    emit sendSizeIndex(index);
}

void NewGame::onDifficultyIndex(int index){
    emit sendDifficultyIndex(index);
}



//QComboBox


//QDialog
