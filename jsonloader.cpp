#include "jsonloader.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

JsonLoader::JsonLoader(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    auto data = file.readAll();

    m_jsonDoc = QJsonDocument::fromJson(data);
}

QStandardItemModel* JsonLoader::makeModel() const
{
    auto model = new QStandardItemModel(0, 2);
    QStandardItem* rootItem = model->invisibleRootItem();
    rootItem->setData("root", Qt::DisplayRole);

    auto rootObj = m_jsonDoc.object();

    for (const auto& lvl1Key : rootObj.keys()) {
        QStandardItem* lvl1Item = new QStandardItem(lvl1Key);
        lvl1Item->setEditable(false);
        rootItem->appendRow(lvl1Item);

        auto lvl2Obj = rootObj[lvl1Key].toObject();
        for (const auto& lvl2Key : lvl2Obj.keys()) {
            QStandardItem* lvl2Item = new QStandardItem(lvl2Key);
            lvl2Item->setEditable(false);
            lvl1Item->appendRow(lvl2Item);

            auto lvl3Obj = lvl2Obj[lvl2Key].toObject();
            for (const auto& lvl3Key : lvl3Obj.keys()) {
                QStandardItem* lvl3Item = new QStandardItem(lvl3Key);
                lvl3Item->setEditable(false);
                lvl2Item->appendRow(lvl3Item);

                auto lvl4Obj = lvl3Obj[lvl3Key].toObject();
                for (const auto& lvl4Key : lvl4Obj.keys()) {
                    QStandardItem* lvl4Item = new QStandardItem(lvl4Key);
                    lvl4Item->setEditable(false);

                    QStandardItem* seriesItem = new QStandardItem();
                    seriesItem->setEditable(false);
                    auto lvl4Values = lvl4Obj[lvl4Key].toArray();
                    seriesItem->setData(lvl4Values);

                    lvl3Item->appendRow({lvl4Item, seriesItem});
                }
            }
        }
    }

    return model;
}
