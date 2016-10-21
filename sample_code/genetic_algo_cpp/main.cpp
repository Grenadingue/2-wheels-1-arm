#include <QtWidgets/QApplication>
#include "Controller.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller geneticAlgoController;

    geneticAlgoController.start();
    return a.exec();
}
