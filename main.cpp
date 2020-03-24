#include "presenter.h"
#include "TestModel.h"
#include <QApplication>
#include <QTranslator>
#include <QPushButton>
#include <iostream>
#include <string.h>
int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage : programm id_programme (0 takuzu, 1 test)" <<std::endl;
        return 0;
    }
    int id_prog;

    if (strncmp("1", argv[1],1) == 0) {
        QApplication a(argc, argv);
        TestModel test;
        return 0;
    }
    if (strncmp("0", argv[1],1) == 0) {
        QApplication a(argc, argv);
        QTranslator translator;
        /*QtCreator create a build folder where it executes the main.
         *  However the *.qm files are still in the folder of development.
         * More research are needed to find another solution.
         */
        /*TODO
         * Setup language detection.
        */
        if(translator.load("takuzu_en","../project_takuzu/")) {
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
