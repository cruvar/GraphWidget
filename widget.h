#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QCustomPlot;

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

private:
    void initControls();
    void initPlotWidget();

private:
    QCustomPlot *plot;

};

#endif // WIDGET_H
