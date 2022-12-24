#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <QJsonDocument>
#include <QString>
#include <QStandardItemModel>


class JsonLoader
{
public:
    JsonLoader(QString fileName);

    QStandardItemModel* makeModel() const;
private:
    QJsonDocument m_jsonDoc;
};

#endif // JSONLOADER_H
