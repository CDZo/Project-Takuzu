#ifndef IOBSERVER_H
#define IOBSERVER_H
class IObserver {
public:
    virtual ~IObserver(){};
    virtual void updateData() = 0;
};
#endif // IOBSERVER_H
