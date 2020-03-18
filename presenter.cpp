#include "presenter.h"
#include "ui_vue.h"
#include <QIcon>

presenter::presenter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::presenter)
{
    /*See
     * https://specifications.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html
     * For more Icon
    */

    ui->setupUi(this);
    ui->actionNew->setIcon(QIcon::fromTheme("document-new"));
    ui->actionOpen->setIcon(QIcon::fromTheme("document-open"));
    ui->actionSave->setIcon(QIcon::fromTheme("document-save"));
    std::cout <<"defaulty";
    std::cout << std::flush;
}

presenter::~presenter()
{
    delete ui;
}
