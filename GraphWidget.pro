#-------------------------------------------------
#
# Project created by QtCreator 2017-07-11T20:08:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = GraphWidget
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qcustomplot/qcustomplot.cpp

HEADERS  += widget.h \
    qcustomplot/qcustomplot.h
