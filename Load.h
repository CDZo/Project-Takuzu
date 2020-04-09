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

private:
    Ui::Load *ui;

public slots:
    void onText(const QString &text);

signals:
    void sendText (const QString &text);
};

#endif // LOAD_H
