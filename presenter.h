#ifndef PRESENTER_H
#define PRESENTER_H

#include <QMainWindow>

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
};

#endif // PRESENTER_H
