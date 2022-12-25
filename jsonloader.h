#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QJsonDocument>
#include <QString>
#include <QStandardItemModel>
#include <QDateTime>


class JsonLoader
{
public:
    JsonLoader(QString fileName);

    QStandardItemModel* makeModel();

    QDateTime minDate() const;
    QDateTime maxDate() const;

private:
    QJsonDocument m_jsonDoc;

    QDateTime m_minDate;
    QDateTime m_maxDate;
};

#endif // JSONLOADER_H
