#include <QLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QStackedWidget>

#include <random>
#include <QDebug>

#include "widget.h"
#include "qcustomplot.h"

using namespace WeaterGraph;

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent)
    , plot(new QCustomPlot(this))
{
    setLayout(new QVBoxLayout);

    // generate atmpsphere data
    Atmosphere atm;
    for(int i = 0; i < 500; ++i) {
        int temper = rand() % ((70 + 1) + 90) - 90;
        int wet = rand()/RAND_MAX * 100;
        atm.temperature.append(static_cast<double>(temper));
        atm.wetness.append(static_cast<double>(wet));
    }

    //generate wind data
    Wind wind;
    for(int i = 0; i < 500; ++i) {
        int direction = rand()/RAND_MAX * 360;
        int speed = rand()/RAND_MAX * 100;
        wind.direction.append(static_cast<double>(direction));
        wind.speed.append(static_cast<double>(speed));
    }

    // generate air data
    Air air;
    for(int i = 0; i < 500; ++i) {
        double density = (double)(rand())/RAND_MAX * 1.3;
        int pressure = rand()/RAND_MAX * 110000;
        air.density.append(static_cast<double>(density));
        air.pressure.append(static_cast<double>(pressure));
    }

    qDebug() << atm.temperature;

    initControls();
    initPlotWidget();
}

GraphWidget::~GraphWidget()
{

}

void GraphWidget::setAtmosphereData(Atmosphere data)
{

}

void GraphWidget::setWindData(Wind data)
{

}

void GraphWidget::setAirData(Air data)
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
}

void GraphWidget::initPlotWidget()
{
    layout()->addWidget(plot);
}
