#include "clock.h"

namespace DesktopClock {
/**
 * @brief Constructor of Clock object.
 * @param QWidget *parent
 */
Clock::Clock(QWidget *parent) :
    QWidget(parent)
{
    setupMeta();
    setupPlugins();
    setupVariables();
    setupChildren();
    setupConnections();
}

/**
 * @brief Function that gets triggered on mouse move event.
 * @param QMouseEvent *event
 */
void Clock::mouseMoveEvent(QMouseEvent *event)
{
    if (!locked) {
        move(event->globalX() - coordX, event->globalY() - coordY);
    }
}

/**
 * @brief Function that gets triggered on mouse press event.
 * @param QMouseEvent *event
 */
void Clock::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        QMenu menu(this);
        menu.addAction(actionChangeColour);
        menu.addAction(actionToggleLocked);
#ifdef Q_OS_WIN
        menu.addAction(actionCopyCurrentTime);
#endif
        menu.addAction(actionQuit);
        menu.exec(mapToGlobal(event->localPos().toPoint()));
    } else if (event->button() == Qt::LeftButton && !locked) {
        QApplication::setOverrideCursor(Qt::OpenHandCursor);

        coordX = event->x();
        coordY = event->y();
    }
}

/**
 * @brief Function that gets triggered on mouse release event.
 * QMouseEvent *
 */
void Clock::mouseReleaseEvent(QMouseEvent *)
{
    if (!locked) {
        QApplication::restoreOverrideCursor();

        QSettings settings;
        settings.setValue("coords", this->pos());
    }
}

/**
 * @brief Function that actually draws visual parts of clock.
 */
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

    time = QTime::currentTime();

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
    QCoreApplication::setOrganizationName("rudissaar");
    QCoreApplication::setOrganizationDomain("murda.eu");
    QCoreApplication::setApplicationName("desktop-clock");

    setParent(nullptr);
    setFixedSize(320, 320);
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnBottomHint);

    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_ShowWithoutActivating);
}

/**
 * @brief Scans for possible plugins and loads them if possible.
 */
void Clock::setupPlugins()
{
    QDir path(QDir::currentPath() + QDir::separator() + "plugins");

    foreach (QString filename, path.entryList(QDir::Files)) {
        loadPlugin(path.absolutePath() + QDir::separator() + filename);
    }
}

/**
 * @brief Sets up initial variable values for Clock object.
 */
void Clock::setupVariables()
{
    QSettings setting;

    QVariant colourData = setting.value("colour");
    colour = (colourData.isValid()) ? colourData.value<QColor>() : Qt::white;

    QVariant lockedData = setting.value("locked");
    locked = (lockedData.isValid()) ? lockedData.toBool() : false;

    QVariant coordsData = setting.value("coords");
    coordX = (coordsData.isValid()) ? coordsData.value<QPoint>().x() : 100;
    coordY = (coordsData.isValid()) ? coordsData.value<QPoint>().y() : 100;
    move(coordX, coordY);
}

/**
 * @brief Sets up children/member object for Clock object.
 */
void Clock::setupChildren()
{
    actionChangeColour = new QAction(this);
    actionChangeColour->setText(tr("Change colour"));
    actionChangeColour->setIcon(QPixmap(":icons/res/change-colour.svg"));

    actionToggleLocked = new QAction(this);
    actionToggleLocked->setCheckable(true);
    actionToggleLocked->setText(tr("Locked"));
    actionToggleLocked->setChecked(locked);

#ifdef Q_OS_WIN
    actionCopyCurrentTime = new QAction(this);
    actionCopyCurrentTime->setIcon(QPixmap(":icons/res/copy.svg"));
    actionCopyCurrentTime->setText(tr("Copy current time"));
#endif

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
#ifdef Q_OS_WIN
    connect(actionCopyCurrentTime, &QAction::triggered, this, &Clock::copyCurrentTime);
#endif
    connect(actionQuit, &QAction::triggered, this, &Clock::quit);
    connect(timer, &QTimer::timeout, this, &Clock::timeout);
}

/**
 * @brief Method that tries to load individual plugin and initialize it.
 * @param QString filename
 */
void Clock::loadPlugin(QString filename)
{
    QPluginLoader loader(filename);
    QObject *possiblePlugin = loader.instance();

    if (possiblePlugin) {
        PluginInterface *plugin = qobject_cast<PluginInterface *>(possiblePlugin);
        plugin->initialize();
    }
}

/**
 * @brief Sets new colour to clock and saves it your local configuration.
 */
void Clock::setColour()
{
    QColor newColour = QColorDialog::getColor(colour, this);

    if (newColour.isValid()) {
        colour = newColour;

        QSettings setting;
        setting.setValue("colour", colour);
    }
}


/**
 * @brief Sets value for private locked property.
 * @param bool lock
 */
void Clock::setLocked(bool lock)
{
    locked = lock;

    QSettings setting;
    setting.setValue("locked", locked);
}

#ifdef Q_OS_WIN
/**
 * @brief Copies current time into your clipboard's buffer.
 */
void Clock::copyCurrentTime()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(time.toString());
}
#endif

/**
 * @brief Function that closes clock application.
 */
void Clock::quit()
{
    QCoreApplication::quit();
}

/**
 * @brief Function that get's executed after every 1 seconds.
 */
void Clock::timeout()
{
    this->update();
}
}
