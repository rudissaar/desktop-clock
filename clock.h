#ifndef CLOCK_H
#define CLOCK_H

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
    QTimer *timer;

    int coordX;
    int coordY;

private slots:
    void timeout();
};

#endif // CLOCK_H
