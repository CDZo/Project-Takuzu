#ifndef PRESENTER_H
#define PRESENTER_H
#include "ModelTakuzu.h"
#include "View.h"
class Presenter
{
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
};

#endif
