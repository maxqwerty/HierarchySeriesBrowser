#ifndef TIMEINTERVALSELECTOR_H
#define TIMEINTERVALSELECTOR_H

#include <QDateTime>
#include <QWidget>

class TimeIntervalSelector : public QWidget
{
    Q_OBJECT
public:
    explicit TimeIntervalSelector(QWidget *parent = nullptr);

    void setGlobalTimeInterval(QDateTime start, QDateTime end);

    QPair<QDateTime, QDateTime> globalTimeRange();
    QPair<QDateTime, QDateTime> selectedTimeRange();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    void paintTickMarks(QPainter* painter);
    void paintRangeHandlers(QPainter* painter);

    int globalMSec();

    int selectedStartPos();
    int selectedEndPos();

    void calcNewSelectedPos(int newX);

signals:
    void timeIntervalSelected(QPair<QDateTime, QDateTime>);

private:
    QDateTime m_globalStart;
    QDateTime m_globalEnd;
    QDateTime m_selectedStart;
    QDateTime m_selectedEnd;

    bool m_isSelectedStart = false;
    bool m_isSelectedEnd = false;
};

#endif // TIMEINTERVALSELECTOR_H
