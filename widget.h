#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "jsonloader.h"
#include "hierarchytree.h"

class QMenu;

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

};
#endif // WIDGET_H
