#include "Save.h"
#include "ui_Save.h"

Save::Save(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Save)
{
    ui->setupUi(this);
    connect(ui->saveName,SIGNAL(textChanged(QString)),this,SLOT(onNameChanged(QString)));
}

Save::~Save()
{
    delete ui;
}

void Save::onNameChanged(const QString &name)
{
   emit saveNameChanged(name);
}
