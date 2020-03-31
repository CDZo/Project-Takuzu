#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QGridLayout>
#include "Presenter.h"

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    ~View();
    QGridLayout * loadPawnOnGrid(Pawn * pawns, const int & size);

private:
    Ui::View *ui;
};

#endif
