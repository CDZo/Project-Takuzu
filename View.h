#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QGridLayout>
#include <QTimeEdit>
#include <QElapsedTimer>
#include "Pawn.h"

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    ~View();
    void loadUi(Pawn * pawns, const int & size);
    void loadTestPawn(Pawn *pawn);

public slots:
    void onTimerTimeout();

private:

    QGridLayout* loadPawnsOnGrid(Pawn * pawns, const int & size);
    Ui::View *ui;
    QTimeEdit *_chronometer;
    QElapsedTimer *_time;
};

#endif
