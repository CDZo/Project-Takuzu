#include <QApplication>
#include <QTranslator>
#include <QPushButton>
#include <iostream>
#include <string.h>
#include "presenter.h"
#include "TestPawn.h"
#include "TestModel.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage : programm id_programme (0 takuzu, 1 test)" <<std::endl;
        return 0;
    }
    if (strncmp("1", argv[1],1) == 0) {
        QApplication a(argc, argv);
        TestPawn testPawn;
        TestModel testModel;
        return 0;
    }
    if (strncmp("0", argv[1],1) == 0) {
        QApplication a(argc, argv);
        QTranslator translator;
        /*TODO
         * Setup language detection.
        */
        if(translator.load(QLocale(),"takuzu","_",":/translation/")) {
            std::cout << "translator loaded"<< std::endl;
        } else {
            std::cout << "translator failed"<< std::endl;
        }
        a.installTranslator(&translator);
        presenter w;

        w.show();
        return a.exec();
    }
    std::cout << "Wrong id_programm" <<std::endl;

}
