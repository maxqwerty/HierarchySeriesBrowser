#include "widget.h"

#include "serieschartitemdelegate.h"
#include "timeintervalselector.h"

#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setMinimumSize(300, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    QMenu* fileMenu = new QMenu("File");
    fileMenu->addAction("Load data...", this, SLOT(openFile()));

    QMenuBar* menuBar = new QMenuBar();
    menuBar->addMenu(fileMenu);

    m_intervalSelector = new TimeIntervalSelector();
    m_intervalSelector->setGlobalTimeInterval(QTime::currentTime(), QTime::currentTime().addSecs(300));
    mainLayout->addWidget(m_intervalSelector);

    m_treeView = new HierarchyTree();
    mainLayout->addWidget(m_treeView);

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
   auto seriesDataDelegate = new SeriesChartItemDelegate();
   m_treeView->setItemDelegateForColumn(1, seriesDataDelegate);
}

