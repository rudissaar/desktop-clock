#ifndef CLOCK_H
#define CLOCK_H

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

    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::Clock *ui;
    QTimer *timer;

private slots:
    void timeout();
};

#endif // CLOCK_H
