#ifndef TIMEINTERVALSELECTOR_H
#define TIMEINTERVALSELECTOR_H

#include <QTime>
#include <QWidget>

class TimeIntervalSelector : public QWidget
{
    Q_OBJECT
public:
    explicit TimeIntervalSelector(QWidget *parent = nullptr);

    void setGlobalTimeInterval(QTime start, QTime end);

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
    void timeIntervalSelected(QTime start, QTime end);

private:
    QTime m_globalStart;
    QTime m_globalEnd;
    QTime m_selectedStart;
    QTime m_selectedEnd;

    bool m_isSelectedStart;
    bool m_isSelectedEnd;
};

#endif // TIMEINTERVALSELECTOR_H
