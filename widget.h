#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QCustomPlot;

namespace WeaterGraph {

struct Atmosphere {
    QVector<double> temperature;
    QVector<double> wetness;
};

struct Wind {
    QVector<double> speed;
    QVector<double> direction;
};

struct Air {
    QVector<double> pressure;
    QVector<double> density;
};


class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

public slots:
    void setAtmosphereData(Atmosphere data);
    void setWindData(Wind data);
    void setAirData(Air data);

private:
    void initControls();
    void initPlotWidget();

private:
    QCustomPlot *plot;

};

} // end namespace GraphWidget

#endif // WIDGET_H
