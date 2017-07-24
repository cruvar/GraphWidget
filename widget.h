#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "qcustomplot/qcustomplot.h"

namespace WeaterGraph {

struct WeaterData {
    QVector<double> height;
    QVector<double> value;
};

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

    void setTemperatureData(WeaterData data);

    void setWetnessData(WeaterData data);

    void setWindSpeedData(WeaterData data);

    void setWindDirectionData(WeaterData data);

    void setAirPressureData(WeaterData data);

    void setAirDensityData(WeaterData data);

public slots:

private:
    void initControls();
    void initPlotWidget();
    void initConnections();

    void generateAtmData(int vectorSize);

private:
    QStackedWidget *swPlots;
    QCustomPlot *atmPlot;
    QCustomPlot *windPlot;
    QCustomPlot *airPlot;
    QComboBox *cbGraphs;

    QCPCurve *temperatureGraph;
    QCPCurve *wetnessGraph;
    QCPCurve *windSpeedGraph;
    QCPCurve *windDirectionGraph;
    QCPCurve *airPressureGraph;
    QCPCurve *airDensityGraph;

};

} // end namespace GraphWidget

#endif // WIDGET_H
