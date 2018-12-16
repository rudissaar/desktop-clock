#include <QApplication>

#include "clock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    rudissaar::Clock clock;
    clock.show();

    return a.exec();
}
