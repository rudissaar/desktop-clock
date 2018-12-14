#ifndef CLOCK_H
#define CLOCK_H

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMouseEvent>
#include <QObject>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QWidget>

namespace Ui {
class Clock;
}

class Clock :
    public QWidget
{
    Q_OBJECT

public:
    explicit Clock(QWidget *parent = nullptr);
    ~Clock();

    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
    QAction *actionQuit;
    QTimer *timer;

    int coordX;
    int coordY;

private slots:
    void quit();
    void timeout();
};

#endif // CLOCK_H
