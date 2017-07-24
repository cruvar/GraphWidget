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
{
    setLayout(new QHBoxLayout);

    initControls();
    initPlotWidget();

    initConnections();

    generateAtmData(100);
}

GraphWidget::~GraphWidget()
{

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
    swPlots = new QStackedWidget(this);
    {
        atmPlot = new QCustomPlot(swPlots);
        windPlot = new QCustomPlot(swPlots);
        airPlot = new QCustomPlot(swPlots);

        atmPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        windPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        airPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

        swPlots->addWidget(atmPlot);
        swPlots->addWidget(windPlot);
        swPlots->addWidget(airPlot);
    }
    swPlots->setMinimumSize(640,360);
    layout()->addWidget(swPlots);

    temperatureGraph    = new QCPCurve(atmPlot->yAxis , atmPlot->xAxis);
    wetnessGraph        = new QCPCurve(atmPlot->yAxis , atmPlot->xAxis);
    windSpeedGraph      = new QCPCurve(windPlot->yAxis, windPlot->xAxis);
    windDirectionGraph  = new QCPCurve(windPlot->yAxis, windPlot->xAxis);
    airPressureGraph    = new QCPCurve(airPlot->yAxis , airPlot->xAxis);
    airDensityGraph     = new QCPCurve(airPlot->yAxis , airPlot->xAxis);

    atmPlot->addPlottable(temperatureGraph);
    atmPlot->addPlottable(wetnessGraph);
    windPlot->addPlottable(windSpeedGraph);
    windPlot->addPlottable(windDirectionGraph);
    airPlot->addPlottable(airPressureGraph);
    airPlot->addPlottable(airDensityGraph);
}

void GraphWidget::initConnections()
{
    connect(cbGraphs,SIGNAL(activated(int)),swPlots,SLOT(setCurrentIndex(int)));
}

void GraphWidget::generateAtmData(int vectorSize)
{
    WeaterData temper;
    for(int i = 0; i < vectorSize; ++i) {
        temper.height.append(i);
        temper.value.append(static_cast<double>(rand() % ((70 + 1) + 90) - 90));
    }
    setTemperatureData(temper);

    WeaterData wet;
    for(int i = 0; i < vectorSize; ++i) {
        wet.height.append(i);
        wet.value.append(static_cast<double>(rand() % 100));
    }
    setWetnessData(wet);

    WeaterData speed;
    for(int i = 0; i < vectorSize; ++i) {
        speed.height.append(i);
        speed.value.append(static_cast<double>(rand() % 100));
    }

    WeaterData direction;
    for(int i = 0; i < vectorSize; ++i) {
        direction.height.append(i);
        direction.value.append(static_cast<double>(rand() % 360));
    }
    WeaterData pressure;
    for(int i = 0; i < vectorSize; ++i) {
        pressure.height.append(i);
        pressure.value.append(static_cast<double>(rand() % 110000));
    }

    WeaterData density;
    for(int i = 0; i < vectorSize; ++i) {
        density.height.append(i);
        density.value.append((double)(rand())/RAND_MAX * 1.3);
    }

}


void GraphWidget::setAirDensityData(WeaterData data)
{
    airDensityGraph->setData(data.height,data.value);
}


void GraphWidget::setAirPressureData(WeaterData data)
{
    airPressureGraph->setData(data.height,data.value);
}



void GraphWidget::setWindDirectionData(WeaterData data)
{
    windDirectionGraph->setData(data.height,data.value);
}


void GraphWidget::setWindSpeedData(WeaterData data)
{
    windSpeedGraph->setData(data.height,data.value);
}


void GraphWidget::setWetnessData(WeaterData data)
{
    wetnessGraph->setData(data.height,data.value);\
    atmPlot->axisRect()->setupFullAxesBox();
    atmPlot->rescaleAxes();
}


void GraphWidget::setTemperatureData(WeaterData data)
{
    temperatureGraph->setData(data.height,data.value);
    atmPlot->axisRect()->setupFullAxesBox();
    atmPlot->rescaleAxes();
}
