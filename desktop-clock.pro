QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = desktop-clock
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
DESTDIR = installer/packages/eu.murda.desktopclock/data

include(submodules/singleapplication/singleapplication.pri)
DEFINES += QAPPLICATION_CLASS=QApplication

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/clock.cpp

HEADERS += \
    src/clock.h \
    src/plugininterface.h

RESOURCES += \
    res.qrc

OTHER_FILES += \
    .gitignore \
    README.md

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
