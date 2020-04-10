#ifndef OPTION_H
#define OPTION_H

#include <QDialog>

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
    void helpIncorrectInRowColumn(Qt::CheckState state);
    void helpUnbalancedRowColumn(Qt::CheckState state);
    void helpIdenticalRowColumn(Qt::CheckState state);

private slots:
    void onIncorrectInRowColumn(int state);
    void onUnbalancedRowColumn(int state);
    void onIdenticalRowColumn(int state);

private:
    Ui::Option *ui;
};

#endif // OPTION_H
