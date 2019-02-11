#ifndef CLOCK_H
#define CLOCK_H

#include <QAction>
#include <QApplication>
#ifdef Q_OS_WIN
#include <QClipboard>
#endif
#include <QColorDialog>
#include <QCursor>
#include <QDir>
#include <QMenu>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPluginLoader>
#include <QSettings>
#include <QTime>
#include <QTimer>
#include <QWidget>

#include "plugininterface.h"

namespace Ui {
class Clock;
}

namespace DesktopClock {
class Clock :
    public QWidget
{
    Q_OBJECT

public:
    explicit Clock(QWidget *parent = nullptr);

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    void setupMeta();
    void setupPlugins();
    void setupVariables();
    void setupChildren();
    void setupConnections();

    void loadPlugin(QString filename);

    QAction *actionChangeColour;
    QAction *actionToggleLocked;
#ifdef Q_OS_WIN
    QAction *actionCopyCurrentTime;
#endif
    QAction *actionQuit;
    QTimer *timer;

    QTime time;
    QColor colour;
    bool locked;

    int coordX;
    int coordY;

private slots:
    void setColour();
    void setLocked(bool);
#ifdef Q_OS_WIN
    void copyCurrentTime();
#endif
    void quit();
    void timeout();
};
}

#endif // CLOCK_H
