#ifndef PAWN_H
#define PAWN_H

#include <QWidget>
#include <QPainter>
#include <iostream>
#include <QPainterPath>
#include <QBrush>
#include "Constant.h"
class Pawn : public QWidget
{
    Q_OBJECT

public:
    ~Pawn();
    class IDesign;
    explicit Pawn(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void setId(const int & id);
    void setFalse(bool isFalse);
    void setLock(bool isLock);
    void setState(const State &state);
    State getState();
    QString getCompleteState();
    bool operator==(const Pawn & other);
    void changeDesignWith(IDesign * newDesign);


public slots:
signals:
    void onClicked(const int id, const State state);

public:
    class IDesign {
    public:
        virtual ~IDesign();
        virtual void displayEmptyPawn(Pawn* pawn) = 0;
        virtual void displayWhitePawn(Pawn* pawn) = 0;
        virtual void displayBlackPawn(Pawn* pawn) = 0;
        virtual void displayLockPawn(Pawn* pawn) = 0;

    };

    class BrightCircle: public IDesign{
       public:
        BrightCircle();
        ~BrightCircle();
        void displayEmptyPawn(Pawn* pawn) override;
        void displayWhitePawn(Pawn* pawn) override;
        void displayBlackPawn(Pawn* pawn) override;
        void displayLockPawn(Pawn* pawn) override;
    };

    class BrightSquare: public IDesign{
       public:
        BrightSquare();
        ~BrightSquare();
        void displayEmptyPawn(Pawn* pawn) override;
        void displayWhitePawn(Pawn* pawn) override;
        void displayBlackPawn(Pawn* pawn) override;
        void displayLockPawn(Pawn* pawn) override;
    };
    class DarkCircle: public IDesign{
       public:
        DarkCircle();
        ~DarkCircle();
        void displayEmptyPawn(Pawn* pawn) override;
        void displayWhitePawn(Pawn* pawn) override;
        void displayBlackPawn(Pawn* pawn) override;
        void displayLockPawn(Pawn* pawn) override;
    };

private:
    IDesign* _design;
    State _state = State::Empty;
    bool _isLock = false;
    bool _isFalse = false;
    int _id = -1;

};

#endif // PAWN_H
