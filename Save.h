#ifndef SAVE_H
#define SAVE_H

#include <QDialog>

namespace Ui {
class Save;
}

class Save : public QDialog
{
    Q_OBJECT

public:
    explicit Save(QWidget *parent = nullptr);
    ~Save();
private slots:
    void onNameChanged(const QString &arg1);
signals:
    void saveNameChanged(const QString &arg1);
private:
    Ui::Save *ui;
};

#endif // SAVE_H
