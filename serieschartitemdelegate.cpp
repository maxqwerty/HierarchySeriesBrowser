#include "serieschartitemdelegate.h"
#include "timeintervalselector.h"

#include <QPainter>
#include <QStyledItemDelegate>
#include <QJsonArray>
#include <QJsonObject>
#include <QAbstractItemModel>

#include <QDebug>

SeriesChartItemDelegate::SeriesChartItemDelegate(TimeIntervalSelector* timeIntervalSelector)
    : m_timeIntervalSelector(timeIntervalSelector)
{
    connect(m_timeIntervalSelector, &TimeIntervalSelector::timeIntervalSelected,
            this, &SeriesChartItemDelegate::onTimeIntervalChanged);
}

QSize SeriesChartItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(100, 25);
}

void SeriesChartItemDelegate::onTimeIntervalChanged(QPair<QTime, QTime> timeRange)
{
    qDebug() << "Selected time range:" << timeRange;
}

void paintSeriesChart(const QJsonArray& seriesArr, const QRect &rect, QPainter* painter) {
    int maxValue = INT_MIN;

    for(auto arrValue : seriesArr) {
        auto obj = arrValue.toObject();
        maxValue = qMax(maxValue, obj["v"].toInt());
    }

    for(int i=0 ; i<seriesArr.size(); ++i) {
        auto obj = seriesArr.at(i).toObject();
        double value = obj["v"].toInt();
        auto valueHeight = rect.height() * value / maxValue;

        painter->drawLine(rect.left() + i, rect.bottom(), rect.left() + i, rect.bottom() - valueHeight);
    }

}

void SeriesChartItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    auto data = index.data(Qt::UserRole + 1);
    if (data.canConvert<QJsonArray>()) {
        auto values = data.value<QJsonArray>();

        paintSeriesChart(values, option.rect, painter);
    }
}
