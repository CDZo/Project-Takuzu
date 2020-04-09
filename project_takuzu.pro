#-------------------------------------------------
#
# Project created by QtCreator 2020-03-10T08:43:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project_takuzu
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Error.cpp \
    Indicator.cpp \
    Load.cpp \
    ModelTakuzu.cpp \
    NewGame.cpp \
    Presenter.cpp \
    Save.cpp \
    TestModel.cpp \
    TestPawn.cpp \
    View.cpp \
    main.cpp \
    Pawn.cpp

HEADERS += \
    Constant.h \
    Error.h \
    IObserver.h \
    ISubject.h \
    Indicator.h \
    Load.h \
    ModelTakuzu.h \
    NewGame.h \
    Presenter.h \
    Save.h \
    TestModel.h \
    TestPawn.h \
    View.h \
    Pawn.h

FORMS += \
        Error.ui \
        Load.ui \
        NewGame.ui \
        Save.ui \
        vue.ui

TRANSLATIONS = takuzu_fr.ts \
    takuzu_en.ts

DISTFILES +=

RESOURCES += \
    grid.qrc \
    translation.qrc

