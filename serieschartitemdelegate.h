#ifndef SERIESCHARTITEMDELEGATE_H
#define SERIESCHARTITEMDELEGATE_H

#include <QAbstractItemDelegate>

class SeriesChartItemDelegate : public QAbstractItemDelegate
{
public:
    SeriesChartItemDelegate();

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // SERIESCHARTITEMDELEGATE_H
