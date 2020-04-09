#include "Load.h"
#include "ui_Load.h"

Load::Load(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Load)
{
    ui->setupUi(this);
    connect(ui->loadName,SIGNAL(textChanged(QString)),this,SLOT(onNameChanged(QString)));
}

Load::~Load()
{
    delete ui;
}

void Load::onNameChanged(const QString &name)
{
    emit loadNameChanged(name);
}
