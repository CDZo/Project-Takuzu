#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>
#include "Constant.h"

namespace Ui {
class NewGame;
}

class NewGame : public QDialog
{
    Q_OBJECT

public:
    explicit NewGame(QWidget *parent = nullptr);
    ~NewGame();



private:
    Ui::NewGame *ui;

public slots:
    void onSizeIndex(int index);
    void onDifficultyIndex(int index);

signals:
    void sendSizeIndex(int index);
    void sendDifficultyIndex(int index);


};

#endif // NEWGAME_H
