#ifndef ISUBJECT_H
#define ISUBJECT_H
#include <QPair>
#include "Constant.h"
#include "IObserver.h"
class ISubject{
public:
    virtual ~ISubject(){};
    virtual void notifyObservers() = 0;
    virtual void addObserver(IObserver * observer) = 0;
    virtual std::pair<int,int> getData(Orientation orientation,int position) = 0;
};

#endif // ISUBJECT_H
