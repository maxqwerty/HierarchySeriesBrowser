#ifndef HIRERARCHYTREE_H
#define HIRERARCHYTREE_H

#include <QTreeView>

class HierarchyTree : public QTreeView
{
    Q_OBJECT
public:
    explicit HierarchyTree(QObject *parent = nullptr);

signals:

};

#endif // HIRERARCHYTREE_H
