#include "clock.h"
#include <QDebug>
#include "ui_clock.h"

Clock::Clock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Clock)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(1000);

    connect(timer, &QTimer::timeout, this, &Clock::timeout);
}

Clock::~Clock()
{
    delete ui;
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
    painter.scale(side / 220.0, side / 220.0);

    for (int i = 0; i < 60; ++i) {
        if ((i % 5) != 0) {
            painter.drawLine(92, 0, 96, 0);
        } else {
            painter.drawLine(86, 0, 96, 0);
        }

        painter.rotate(6.0);
    }

    QTime time = QTime::currentTime();

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
