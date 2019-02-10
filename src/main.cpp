#include <QApplication>
#include <singleapplication.h>

#include "clock.h"

int main(int argc, char *argv[])
{
    SingleApplication app(argc, argv);

    DesktopClock::Clock clock;
    clock.show();

    return app.exec();
}
