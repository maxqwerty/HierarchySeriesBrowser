#include "widget.h"

#include "serieschartitemdelegate.h"
#include "timeintervalselector.h"

#include <QFileDialog>
#include <QHeaderView>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(300, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    QMenu* fileMenu = new QMenu("File");
    fileMenu->addAction("Load data...", this, SLOT(openFile()));
    QMenu* actionMenu = new QMenu("Action");

    QMenuBar* menuBar = new QMenuBar();
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(actionMenu);

    QHBoxLayout* intervalSelectorLayout = new QHBoxLayout();
    m_intervalSelector = new TimeIntervalSelector();
    m_intervalSelectorSpacer = new QWidget();
    m_intervalSelectorSpacer->setFixedWidth(0);
    intervalSelectorLayout->addWidget(m_intervalSelectorSpacer);
    intervalSelectorLayout->addWidget(m_intervalSelector);
    mainLayout->addLayout(intervalSelectorLayout);

    m_treeView = new HierarchyTree();
    mainLayout->addWidget(m_treeView);

    actionMenu->addAction("Expand all", m_treeView, SLOT(expandAll()));
    actionMenu->addAction("Collapse all", m_treeView, SLOT(collapseAll()));
    actionMenu->addAction("Delete selected", this, SLOT(deleteSelected()));

    connect(m_treeView->header(), &QHeaderView::sectionResized,
            this, &Widget::onHeaderResized);

    connect(m_intervalSelector, SIGNAL(timeIntervalSelected(QPair<QDateTime, QDateTime>)),
            m_treeView->viewport(), SLOT(update()));

    mainLayout->setMenuBar(menuBar);
}

Widget::~Widget()
{
}

void Widget::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Data File"),
                                                    "../HirerarchySeriesBrowser/data",
                                                    tr("Data file (*.json)"));

    m_dataLoader = new JsonLoader(fileName);
    m_treeView->setModel(m_dataLoader->makeModel());
    m_intervalSelector->setGlobalTimeInterval(m_dataLoader->minDate(), m_dataLoader->maxDate());
    m_intervalSelectorSpacer->setFixedWidth(m_treeView->header()->sectionSize(0));

    auto seriesDataDelegate = new SeriesChartItemDelegate(m_intervalSelector);
    m_treeView->setItemDelegateForColumn(1, seriesDataDelegate);
}

void Widget::onHeaderResized(int logicalIndex, int oldSize, int newSize)
{
    if (logicalIndex == 0) {
        m_intervalSelectorSpacer->setFixedWidth(newSize);
    }
}

void Widget::deleteSelected()
{
    auto selected = m_treeView->selectionModel()->currentIndex();

    if (selected.isValid()) {
        m_treeView->model()->removeRow(selected.row(), selected.parent());
    }
}

