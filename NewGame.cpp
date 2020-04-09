#include "NewGame.h"
#include "ui_NewGame.h"

NewGame::NewGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGame)
{
    ui->setupUi(this);

}

NewGame::~NewGame()
{
    delete ui;
}



//QComboBox


//QDialog
