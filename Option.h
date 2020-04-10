#ifndef OPTION_H
#define OPTION_H

#include <QDialog>
#include "Constant.h"
namespace Ui {
class Option;
}

class Option : public QDialog
{
    Q_OBJECT

public:
    explicit Option(QWidget *parent = nullptr);
    ~Option();
signals:
    void pawnDesignChanged(PawnDesign design);
    void helpIncorrectInRowColumn(Qt::CheckState state);
    void helpUnbalancedRowColumn(Qt::CheckState state);
    void helpIdenticalRowColumn(Qt::CheckState state);
    void helpIndicator(Qt::CheckState state);
private slots:
    void onDesignChanged(int design);
    void onIncorrectInRowColumn(int state);
    void onUnbalancedRowColumn(int state);
    void onIdenticalRowColumn(int state);
    void onIndicatorChanged(int state);

private:
    Ui::Option *ui;
};

#endif // OPTION_H
