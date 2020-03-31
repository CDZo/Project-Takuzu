#ifndef PRESENTER_H
#define PRESENTER_H
#include "ModelTakuzu.h"

class Presenter
{
public:
    Presenter();
    ~Presenter();
    void createGrid(const int & size, const int & difficulty);
private:
    ModelTakuzu *_model;
    Pawn *_visualPawns;
    int _size = 0;
};

#endif
