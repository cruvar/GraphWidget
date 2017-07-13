#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "qcustomplot.h"

namespace WeaterGraph {

struct WeaterData {
    QVector<double> height;
    QVector<double> value;
};

enum Plot {
    Temperature,
    Wetness,
    WindSpeed,
    WindDirection,
    AirPressure,
    AirDensity
};

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

public slots:
    void setWeaterData(WeaterData data, Plot type);

private:
    void initControls();
    void initPlotWidget();

    void generateAtmData();

private:
    QCustomPlot *plot;

};

} // end namespace GraphWidget

#endif // WIDGET_H
