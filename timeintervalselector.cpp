#include "timeintervalselector.h"

#include <QtMath>
#include <QPainter>
#include <QMouseEvent>

#include <QDebug>

static const int HANDLER_WIDTH = 12;

TimeIntervalSelector::TimeIntervalSelector(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(100, 50);
}

void TimeIntervalSelector::setGlobalTimeInterval(QTime start, QTime end)
{
    m_globalStart = start;
    m_globalEnd = end;
    m_selectedStart = start;
    m_selectedEnd = end;

    update();
}

void TimeIntervalSelector::mousePressEvent(QMouseEvent* event)
{
    if (event->x() > selectedStartPos() && event->x() < (selectedStartPos() + HANDLER_WIDTH)) {
        m_isSelectedStart = true;
    }
    if (event->x() > (selectedEndPos() - HANDLER_WIDTH) && event->x() < selectedEndPos()) {
        m_isSelectedEnd = true;
    }
}

void TimeIntervalSelector::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton) {
        calcNewSelectedPos(event->pos().x());
    }
}

void TimeIntervalSelector::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton) {
        calcNewSelectedPos(event->pos().x());
    }

    m_isSelectedStart = false;
    m_isSelectedEnd = false;
}

void TimeIntervalSelector::resizeEvent(QResizeEvent* event)
{
    // TODO: handle resize to recalc handlers
}

void TimeIntervalSelector::calcNewSelectedPos(int newX)
{
    if (m_isSelectedStart) {
        int newPos = qBound(0, newX,selectedEndPos() - 2 * HANDLER_WIDTH);
        int newMSecTime = (float)globalMSec() / width() * newPos;

        m_selectedStart = m_globalStart.addMSecs(newMSecTime);

        update();
    }

    if (m_isSelectedEnd) {
        int newPos = qBound(selectedStartPos() + 2 * HANDLER_WIDTH + 2, newX, width());
        int newMSecTime = (float)globalMSec() / width() * newPos;

        m_selectedEnd = m_globalStart.addMSecs(newMSecTime);

        update();
    }
}

void TimeIntervalSelector::paintEvent(QPaintEvent* event)
{
    if (m_globalStart.isNull() || m_globalEnd.isNull() || m_selectedStart.isNull() || m_selectedEnd.isNull()) {
        QWidget::paintEvent(event);
        return;
    }

    QPainter painter(this);
    painter.setPen(QColor(Qt::black));
    painter.drawRect(0, 0, width()-1, height()-1);

    paintTickMarks(&painter);
    paintRangeHandlers(&painter);
}

void TimeIntervalSelector::paintTickMarks(QPainter* painter)
{
    painter->save();

    int totalMSec = globalMSec();

    static const int STEP = 100;
    int delta = STEP;
    for (int i=STEP; i < totalMSec; i+=STEP) {
        int ticks = totalMSec / i;
        if ((width() / ticks) >= 10) {
            delta = width() / ticks;
            break;
        }
    }

    painter->setPen(QColor(Qt::blue));
    for (int x=0; x < width(); x += delta) {
        painter->drawLine(x, height(), x, height()-10);
    }

    painter->restore();
}

void TimeIntervalSelector::paintRangeHandlers(QPainter* painter)
{
    painter->save();

    painter->setPen(QColor(Qt::red));

    QFont font;
    font.setPixelSize(10);
    painter->setFont(font);
    painter->rotate(-90);


    painter->drawRect(-40, selectedStartPos(), 40, HANDLER_WIDTH);
    painter->drawText(-40, selectedStartPos() + 10, m_selectedStart.toString());

    painter->drawRect(-40, selectedEndPos() - HANDLER_WIDTH - 1, 40, HANDLER_WIDTH);
    painter->drawText(-40, selectedEndPos() - 3, m_selectedEnd.toString());

    painter->restore();
}

int TimeIntervalSelector::globalMSec()
{
    return m_globalStart.msecsTo(m_globalEnd);
}

int TimeIntervalSelector::selectedStartPos()
{
    return ((float)width() / globalMSec()) * m_globalStart.msecsTo(m_selectedStart);
}

int TimeIntervalSelector::selectedEndPos()
{
    return ((float)width() / globalMSec()) * m_globalStart.msecsTo(m_selectedEnd);
}
