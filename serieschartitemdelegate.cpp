#include "serieschartitemdelegate.h"

#include <QPainter>
#include <QStyledItemDelegate>
#include <QJsonArray>
#include <QJsonObject>
#include <QAbstractItemModel>

#include <QDebug>

SeriesChartItemDelegate::SeriesChartItemDelegate()
{

}

QSize SeriesChartItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(100, 25);
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
