#ifndef PRESENTER_H
#define PRESENTER_H
#include <QObject>
#include "ModelTakuzu.h"
#include "View.h"
class Presenter: public QObject
{
    Q_OBJECT
public:
    Presenter();
    ~Presenter();
    void createGrid(const int & size, const int & difficulty);
    void show();
private:
    View *_view;
    ModelTakuzu *_model;
    Pawn *_visualPawns;
    int _size = 0;
public slots:
    void onPawnClicked(const int & id, const State & state);
signals:
    void pawnChanged(const int & id, const State & state);
};

#endif
