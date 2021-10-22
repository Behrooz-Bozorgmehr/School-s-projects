#include "factory.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Factory fact;
    fact.build();

    return a.exec();
}
