#include <QLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QStackedWidget>

#include <random>
#include <QDebug>

#include "widget.h"

using namespace WeaterGraph;

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent)
    , plot(new QCustomPlot(this))
{
    setLayout(new QHBoxLayout);

    initControls();
    initPlotWidget();

    generateAtmData();
}

GraphWidget::~GraphWidget()
{

}

void GraphWidget::setWeaterData(WeaterData data, Plot type)
{
    plot->removeGraph(type);
    plot->addGraph();
    plot->graph(type)->setData(data.value, data.height);

    plot->xAxis->setLabel("Temperature");
    plot->yAxis->setLabel("Height");

    plot->xAxis->setRange(-90, 70);
    plot->yAxis->setRange(0, 500);

    plot->replot();
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

        wControls->setLayout(new QVBoxLayout);
        wControls->setMaximumWidth(200);
        wControls->layout()->setMargin(0);
        wControls->layout()->setAlignment(Qt::AlignTop);
        wControls->layout()->addWidget(new QLabel(tr("График:")));
        wControls->layout()->addWidget(cbGraphs);
    }
    layout()->addWidget(wControls);
}

void GraphWidget::initPlotWidget()
{
    plot->setMinimumSize(640,360);
    layout()->addWidget(plot);
}

void GraphWidget::generateAtmData()
{
    WeaterData temper;
    for(int i = 0; i < 500; ++i) {
        temper.height.append(i);
        temper.value.append(static_cast<double>(rand() % ((70 + 1) + 90) - 90));
    }
    setWeaterData(temper, Temperature);

    WeaterData wet;
    for(int i = 0; i < 500; ++i) {
        wet.height.append(i);
        wet.value.append(static_cast<double>(rand()/RAND_MAX * 100));
    }

    WeaterData speed;
    for(int i = 0; i < 500; ++i) {
        speed.height.append(i);
        speed.value.append(static_cast<double>(rand()/RAND_MAX * 100));
    }

    WeaterData direction;
    for(int i = 0; i < 500; ++i) {
        direction.height.append(i);
        direction.value.append(static_cast<double>(rand()/RAND_MAX * 360));
    }

    WeaterData pressure;
    for(int i = 0; i < 500; ++i) {
        pressure.height.append(i);
        pressure.value.append(static_cast<double>(rand()/RAND_MAX * 110000));
    }

    WeaterData density;
    for(int i = 0; i < 500; ++i) {
        density.height.append(i);
        density.value.append((double)(rand())/RAND_MAX * 1.3);
    }
}
