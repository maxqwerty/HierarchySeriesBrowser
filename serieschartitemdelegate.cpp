#include "serieschartitemdelegate.h"
#include "timeintervalselector.h"

#include <QPainter>
#include <QStyledItemDelegate>
#include <QJsonArray>
#include <QJsonObject>
#include <QAbstractItemModel>
#include <QMap>

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

void SeriesChartItemDelegate::onTimeIntervalChanged(QPair<QDateTime, QDateTime> timeRange)
{
    qDebug() << "Selected time range:" << timeRange;
}

void SeriesChartItemDelegate::paintSeriesChart(const QJsonArray& seriesArr, const QRect &rect, QPainter* painter)const {
    auto selectedRange = m_timeIntervalSelector->selectedTimeRange();
    int msInterval = selectedRange.first.msecsTo(selectedRange.second);
    int msecPerPixel = (float)msInterval / rect.width();

    QMap<int, int> chartValues;
    for(auto arrValue : seriesArr) {
        auto obj = arrValue.toObject();

        auto time = QDateTime::fromString(obj["t"].toString(), Qt::ISODateWithMs);
        auto value = obj["v"].toInt();

        if (time < selectedRange.first || time > selectedRange.second) {
            continue;
        }

        int pixelIndex = selectedRange.first.msecsTo(time) / msecPerPixel;
        if (!chartValues.contains(pixelIndex)) {
            chartValues[pixelIndex] = 0;
        }

        chartValues[pixelIndex] += value;
    }

    int maxValue = INT_MIN;

    for(auto v: chartValues.values()) {
        maxValue = qMax(maxValue, v);
    }

    for(auto pixel : chartValues.keys()) {
        int valueHeight = (float)chartValues[pixel] / maxValue * rect.height();

        if (chartValues.contains(pixel)) {
            painter->drawLine(rect.left() + pixel, rect.bottom(), rect.left() + pixel, rect.bottom() - valueHeight);
        }
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
