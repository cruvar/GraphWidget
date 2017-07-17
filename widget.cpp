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

    generateAtmData(100);
    changePlot(0);
}

GraphWidget::~GraphWidget()
{

}

void GraphWidget::setWeaterData(WeaterData data, Plot type)
{
    plot->removeGraph(type);
    plot->addGraph();
    plot->graph(type)->setData(data.value, data.height);
    plot->graph(type)->setVisible(false);
}

void GraphWidget::setGraphColor(const QColor &color, Plot type)
{
    plot->graph(type)->setPen(QPen(color));
}

void GraphWidget::changePlot(int index)
{
    for(int i = 0; i < plot->graphCount(); ++i)
        plot->graph(i)->setVisible(false);

    if(index == 0 && plot->graphCount() > Wetness) {
        plot->graph(Temperature)->setVisible(true);
        plot->graph(Wetness)->setVisible(true);
        plot->xAxis->setLabel("Temperature");
        plot->xAxis2->setLabel("Wetness");
        plot->xAxis->setRange(-90,70);
        plot->xAxis2->setRange(0,100);
    }
    if(index == 1 && plot->graphCount() > WindDirection) {
        plot->graph(WindSpeed)->setVisible(true);
        plot->graph(WindDirection)->setVisible(true);
        plot->xAxis->setLabel("WindSpeed");
        plot->xAxis2->setLabel("WindDirection");
        plot->xAxis->setRange(0,100);
        plot->xAxis2->setRange(0,360);
    }
    if(index == 2 && plot->graphCount() > AirDensity) {
        plot->graph(AirPressure)->setVisible(true);
        plot->graph(AirDensity)->setVisible(true);
        plot->xAxis->setLabel("AirPressure");
        plot->xAxis2->setLabel("AirDensity");
        plot->xAxis->setRange(0,110000);
        plot->xAxis2->setRange(0,1.3);
    }
    plot->yAxis->setLabel("Height");
    plot->xAxis2->setVisible(true);
    plot->rescaleAxes(true);

    plot->replot();
}


void GraphWidget::initControls()
{
    QWidget *wControls = new QWidget(this);
    {
        cbGraphs = new QComboBox(wControls);
        cbGraphs->addItems(QStringList()
                           << tr("Температура, влажность")
                           << tr("Скорость, направление ветра")
                           << tr("Давление, плотность")
                           );
        connect(cbGraphs,SIGNAL(activated(int)),this,SLOT(changePlot(int)));

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

void GraphWidget::generateAtmData(int vectorSize)
{
    WeaterData temper;
    for(int i = 0; i < vectorSize; ++i) {
        temper.height.append(i);
        temper.value.append(static_cast<double>(rand() % ((70 + 1) + 90) - 90));
    }
    setWeaterData(temper, Temperature);
    setGraphColor(Qt::darkYellow, Temperature);

    WeaterData wet;
    for(int i = 0; i < vectorSize; ++i) {
        wet.height.append(i);
        wet.value.append(static_cast<double>(rand() % 100));
    }
    setWeaterData(wet, Wetness);
    setGraphColor(Qt::darkGreen, Wetness);

    WeaterData speed;
    for(int i = 0; i < vectorSize; ++i) {
        speed.height.append(i);
        speed.value.append(static_cast<double>(rand() % 100));
    }
    setWeaterData(speed, WindSpeed);
    setGraphColor(Qt::blue, WindSpeed);

    WeaterData direction;
    for(int i = 0; i < vectorSize; ++i) {
        direction.height.append(i);
        direction.value.append(static_cast<double>(rand() % 360));
    }
    setWeaterData(direction, WindDirection);
    setGraphColor(Qt::red, WindDirection);

    WeaterData pressure;
    for(int i = 0; i < vectorSize; ++i) {
        pressure.height.append(i);
        pressure.value.append(static_cast<double>(rand() % 110000));
    }
    setWeaterData(pressure, AirPressure);
    setGraphColor(Qt::magenta, AirPressure);

    WeaterData density;
    for(int i = 0; i < vectorSize; ++i) {
        density.height.append(i);
        density.value.append((double)(rand())/RAND_MAX * 1.3);
    }
    setWeaterData(density, AirDensity);
    setGraphColor(Qt::green, AirDensity);


    qDebug() << density.value;
}
