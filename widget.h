#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "jsonloader.h"
#include "hierarchytree.h"

class TimeIntervalSelector;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void openFile();

private:
    JsonLoader* m_dataLoader;
    HierarchyTree* m_treeView;
    TimeIntervalSelector* m_intervalSelector;

};
#endif // WIDGET_H
