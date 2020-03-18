#include "presenter.h"
#include <QApplication>
#include <QTranslator>
#include <QPushButton>
#include <iostream>
int main(int argc, char *argv[])
{
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
