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
}

View::~View()
{
    delete ui;
}

QGridLayout *View::loadPawnOnGrid(Pawn * pawns, const int & size)
{
    QGridLayout *gridLayout = new QGridLayout(this);
    for (int row = 0; row < size; row++) {
        for (int column = 0; column <size; column++) {
            gridLayout->addWidget(&pawns[ row * size + column],row,column);
        }
    }
    return gridLayout;
}
