#ifndef INFORMATION_H
#define INFORMATION_H

#include <QDialog>

namespace Ui {
class Information;
}

class Information : public QDialog
{
    Q_OBJECT

public:
    explicit Information(QWidget *parent = nullptr);
    ~Information();
    void setInformationTextWith(const QString & information);

private:
    Ui::Information *ui;
};

#endif // INFORMATION_H
