#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>

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
};

#endif // NEWGAME_H
