#include "clock.h"

namespace rudissaar
{
    /**
     * @brief Constructor of Clock object.
     * @param QWidget *parent
     */
    Clock::Clock(QWidget *parent) :
        QWidget(parent)
    {
        setupMeta();
        setupVariables();
        setupChildren();
        setupConnections();
    }

    void Clock::mouseMoveEvent(QMouseEvent *event)
    {
        if (!locked) {
            move(event->globalX() - coordX, event->globalY() - coordY);
        }
    }

    void Clock::mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::RightButton) {
            QMenu menu(this);
            menu.addAction(actionChangeColour);
            menu.addAction(actionToggleLocked);
            menu.addAction(actionQuit);
            menu.exec(mapToGlobal(event->localPos().toPoint()));
        } else if (event->button() == Qt::LeftButton && !locked) {
            coordX = event->x();
            coordY = event->y();
        }
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
        painter.setPen(colour);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.translate(width() / 2, height() / 2);
        painter.scale(side / 240.0, side / 240.0);

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
        painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
        painter.setPen(Qt::NoPen);
        painter.setBrush(colour);
        painter.drawConvexPolygon(hourHand, 3);
        painter.restore();

        painter.save();
        painter.rotate((time.minute() * 360) / 60.0);
        painter.setPen(Qt::NoPen);
        painter.setBrush(colour);
        painter.drawConvexPolygon(minuteHand, 3);
        painter.restore();

        painter.save();
        painter.rotate((time.second() * 360) / 60);
        painter.setPen(Qt::NoPen);
        painter.setBrush(colour);
        painter.drawConvexPolygon(secondHand, 3);
        painter.restore();
    }

    /**
     * @brief Sets up necessary flags and attributes for Clock object.
     */
    void Clock::setupMeta()
    {
        setParent(nullptr);
        setFixedSize(320, 320);
        setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnBottomHint);

        setAttribute(Qt::WA_NoSystemBackground, true);
        setAttribute(Qt::WA_TranslucentBackground, true);
        setAttribute(Qt::WA_ShowWithoutActivating);

    }

    /**
     * @brief Sets up initial variable values for Clock object.
     */
    void Clock::setupVariables()
    {
        colour = Qt::white;
        locked = false;
    }

    /**
     * @brief Sets up children/member object for Clock object.
     */
    void Clock::setupChildren()
    {
        actionChangeColour = new QAction(this);
        actionChangeColour->setText(tr("Change colour"));

        actionToggleLocked = new QAction(this);
        actionToggleLocked->setCheckable(true);
        actionToggleLocked->setText(tr("Locked"));

        actionQuit = new QAction(this);
        actionQuit->setIcon(QPixmap(":icons/res/close.svg"));
        actionQuit->setText(tr("Close"));

        timer = new QTimer(this);
        timer->start(1000);
    }

    /**
     * @brief Sets up connections between children/member objects for Clock object.
     */
    void Clock::setupConnections()
    {
        connect(actionChangeColour, &QAction::triggered, this, &Clock::setColour);
        connect(actionToggleLocked, &QAction::toggled, this, &Clock::setLocked);
        connect(actionQuit, &QAction::triggered, this, &Clock::quit);
        connect(timer, &QTimer::timeout, this, &Clock::timeout);
    }

    void Clock::setColour()
    {
        colour = QColorDialog::getColor(colour, this);
    }

    void Clock::setLocked(bool lock)
    {
        locked = lock;
    }

    void Clock::quit()
    {
        QCoreApplication::quit();
    }

    void Clock::timeout()
    {
        this->update();
    }
}
