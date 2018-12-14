#include "clock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Clock clock;
    clock.show();

    return a.exec();
}
