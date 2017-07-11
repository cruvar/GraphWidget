#include <QLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QStackedWidget>

#include <QDebug>

#include "widget.h"
#include "qcustomplot.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent)
    , plot(new QCustomPlot(this))
{
    setLayout(new QVBoxLayout);

    initControls();
    initPlotWidget();
}

GraphWidget::~GraphWidget()
{

}

void GraphWidget::initControls()
{
    QWidget *wControls = new QWidget(this);
    {
        QComboBox *cbGraphs = new QComboBox(wControls);
        cbGraphs->addItems(QStringList()
                           << tr("Температура, влажность")
                           << tr("Скорость, направление ветра")
                           << tr("Давление, плотность")
                           );

//        QStackedWidget *swGraphControls = new QStackedWidget(gbSidePanel);

        wControls->setLayout(new QHBoxLayout);
        wControls->layout()->setMargin(0);
        wControls->layout()->setAlignment(Qt::AlignLeft);
        wControls->layout()->addWidget(new QLabel(tr("График:")));
        wControls->layout()->addWidget(cbGraphs);
    }
    wControls->setFixedHeight(20);
    layout()->addWidget(wControls);
//    qDebug() << wControls->height();
}

void GraphWidget::initPlotWidget()
{
    layout()->addWidget(plot);
}
