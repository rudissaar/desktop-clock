#ifndef CLOCK_H
#define CLOCK_H

#include <QAction>
#include <QApplication>
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

namespace rudissaar {
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
    QAction *actionQuit;
    QTimer *timer;

    QColor colour;
    bool locked;

    int coordX;
    int coordY;

private slots:
    void setColour();
    void setLocked(bool);
    void quit();
    void timeout();
};
}

#endif // CLOCK_H
