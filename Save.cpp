#include "Save.h"
#include "ui_Save.h"

Save::Save(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Save)
{
    ui->setupUi(this);
    connect(ui->saveNameEdit,SIGNAL(textChanged(QString)),this,SLOT(onText(QString)));
}

Save::~Save()
{
    delete ui;
}

void Save::onText(const QString &text)
{
    emit sendText(text);
}
