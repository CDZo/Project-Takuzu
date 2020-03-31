#ifndef PRESENTER_H
#define PRESENTER_H

#include <QMainWindow>
#include <QFile>
#include <QString>
#include "ModelTakuzu.h"


namespace Ui {
class presenter;
}

class presenter : public QMainWindow
{
    Q_OBJECT

public:
    explicit presenter(QWidget *parent = 0);
    void createGrid(int size, int difficulty); //difficulty is an int, if =0 -> easy, if =1 -> hard
    ~presenter();

private:
    Ui::presenter *ui;
    ModelTakuzu *_model;
};

#endif // PRESENTER_H
