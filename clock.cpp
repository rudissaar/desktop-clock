#include "clock.h"
#include <QDebug>

Clock::Clock(QWidget *parent) :
    QWidget(parent)
{
    setParent(nullptr);

    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnBottomHint);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_ShowWithoutActivating);

    timer = new QTimer(this);
    timer->start(1000);

    connect(timer, &QTimer::timeout, this, &Clock::timeout);
}

Clock::~Clock()
{

}

void Clock::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalX() - coordX, event->globalY() - coordY);
}

void Clock::mousePressEvent(QMouseEvent *event)
{
    coordX = event->x();
    coordY = event->y();
}

void Clock::paintEvent(QPaintEvent *)
{
    static const QPoint hourHand[3] = {
        QPoint(4, 4),
        QPoint(-4, 4),
        QPoint(0, -40)
    };

    static const QPoint minuteHand[3] = {
        QPoint(4, 4),
        QPoint(-4, 4),
        QPoint(0, -70)
    };

    static const QPoint secondHand[3] = {
        QPoint(2, 2),
        QPoint(-2, 2),
        QPoint(0, -90)
    };

    int side = qMin(width(), height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 400.0, side / 400.0);

    for (int i = 0; i < 60; ++i) {
        if ((i % 5) != 0) {
            painter.drawLine(92, 0, 96, 0);
        } else {
            painter.drawLine(86, 0, 96, 0);
        }

        painter.rotate(6.0);
    }

    QTime time = QTime::currentTime();
    qDebug() << ((time.hour() * 360) / 12);

    painter.save();
    painter.rotate((time.hour() * 360) / 12);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    painter.save();
    painter.rotate((time.minute() * 360) / 60);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    painter.save();
    painter.rotate((time.second() * 360) / 60);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();
}

void Clock::timeout()
{
    this->update();
}
