#include "Load.h"
#include "ui_Load.h"

Load::Load(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Load)
{
    ui->setupUi(this);
    connect(ui->loadNameEdit,SIGNAL(textChanged(QString)),this,SLOT(onText(QString)));
}

Load::~Load()
{
    delete ui;
}

void Load::onText(const QString &text)
{
    emit sendText(text);
}
