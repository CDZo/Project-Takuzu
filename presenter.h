#ifndef PRESENTER_H
#define PRESENTER_H

#include <QMainWindow>
#include "ModelTakuzu.h"
namespace Ui {
class presenter;
}

class presenter : public QMainWindow
{
    Q_OBJECT

public:
    explicit presenter(QWidget *parent = 0);
    ~presenter();

private:
    Ui::presenter *ui;
    ModelTakuzu *_model;
};

#endif // PRESENTER_H
