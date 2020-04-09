#ifndef LOAD_H
#define LOAD_H

#include <QDialog>

namespace Ui {
class Load;
}

class Load : public QDialog
{
    Q_OBJECT

public:
    explicit Load(QWidget *parent = nullptr);
    ~Load();

private slots:
    void onNameChanged(const QString &arg1);
signals:
    void loadNameChanged(const QString &arg1);
private:
    Ui::Load *ui;
};

#endif // LOAD_H
