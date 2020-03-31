#include "View.h"
#include "ui_vue.h"
#include <QIcon>
#include <QLineEdit>
#include <QTextStream>
#include <QRandomGenerator>
#include <QIODevice>


View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);

    ui->actionNew->setIcon(QIcon::fromTheme("document-new"));
    ui->actionOpen->setIcon(QIcon::fromTheme("document-open"));
    ui->actionSave->setIcon(QIcon::fromTheme("document-save"));

}

View::~View()
{
    delete ui;
}

void View::loadPawnsOnGrid(Pawn * pawns, const int & size)
{
    QGridLayout *gridLayout = new QGridLayout(this);
    for (int row = 0; row < size; row++) {
        for (int column = 0; column <size; column++) {
            gridLayout->addWidget(&pawns[ row * size + column],row,column);
        }
    }
    gridLayout->addWidget(ui->pushButton,size,0,1,size);
    ui->centralWidget->setLayout(gridLayout);
}
