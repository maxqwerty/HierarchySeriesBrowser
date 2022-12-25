#ifndef SERIESCHARTITEMDELEGATE_H
#define SERIESCHARTITEMDELEGATE_H

#include <QAbstractItemDelegate>

class TimeIntervalSelector;

class SeriesChartItemDelegate : public QAbstractItemDelegate
{
public:
    SeriesChartItemDelegate(TimeIntervalSelector* timeIntervalSelector);

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private slots:
    void onTimeIntervalChanged(QPair<QDateTime, QDateTime> timeRange);

private:
    void paintSeriesChart(const QJsonArray& seriesArr, const QRect &rect, QPainter* painter)const;

private:
    TimeIntervalSelector* m_timeIntervalSelector;
};

#endif // SERIESCHARTITEMDELEGATE_H
