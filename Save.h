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

private:
    Ui::Save *ui;

public slots:
    void onText(const QString &text);

signals:
    void sendText (const QString &text);
};

#endif // SAVE_H
