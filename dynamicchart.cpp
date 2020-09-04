#include "dynamicchart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <iostream>

DynamicChart::DynamicChart(QGraphicsItem *parent, Qt::WindowFlags wFlags): QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axisX(new QValueAxis()),
    m_axisY(new QValueAxis()),
//    m_step(0),
    m_x(0),
    m_y(0),
    xBegin(-5),
    xEnd(20),
    yBegin(-1),
    yEnd(1)
{
    pom="sluzy do nowego commitu";
QObject::connect(this, &DynamicChart::updateChart, this, &DynamicChart::handleTimeout);
    m_series = new QSplineSeries(this);
    green.setWidth(3);
    m_series->setPen(green);
    m_series->append(m_x, m_y);
    addSeries(m_series);
    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
    m_axisX->setTickCount(10);
    m_axisX->setRange(xBegin, xEnd);
    m_axisY->setRange(yBegin,yEnd);
}

DynamicChart::DynamicChart(std::string PenColor,double xHalfRange1,double yHalfRange1,double xValueNow,double yValueNow,int horizontallyLines,int verticallyLines, QGraphicsItem *parent, Qt::WindowFlags wFlags): QChart(QChart::ChartTypeCartesian, parent, wFlags),
m_series(0),
m_axisX(new QValueAxis()),
m_axisY(new QValueAxis()),
//m_step(0),
m_x(0),
m_y(0)
{
    xHalfRange=xHalfRange1/2;
    yHalfRange=yHalfRange1/2;
    xBegin=xValueNow-xHalfRange;
    xEnd=xValueNow+xHalfRange;
    yBegin=yValueNow-yHalfRange;
    yEnd=yValueNow+yHalfRange;

    QObject::connect(this, &DynamicChart::updateChart, this, &DynamicChart::handleTimeout);

    m_series = new QSplineSeries(this);
    if("black"==PenColor){green.setColor(Qt::black);}
    else if("cyan"==PenColor){green.setColor(Qt::cyan);}
    else if("red"==PenColor){green.setColor(Qt::red);}
    else if("dark red"==PenColor){green.setColor(Qt::darkRed);}
    else if("magenta"==PenColor){green.setColor(Qt::magenta);}
    else if("green"==PenColor){green.setColor(Qt::green);}
    else if("yellow"==PenColor){green.setColor(Qt::yellow);}
    else if("dark yellow"==PenColor){green.setColor(Qt::darkYellow);}
    else if("blue"==PenColor){green.setColor(Qt::blue);}
    else if("gray"==PenColor){green.setColor(Qt::gray);}

    green.setWidth(3);
    m_series->setPen(green);
    m_series->append(m_x, m_y);

    addSeries(m_series);

    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);

    if(horizontallyLines>2)
    m_axisX->setTickCount(horizontallyLines);
    else
        m_axisX->setTickCount(10);
    if(verticallyLines>2)
    m_axisY->setTickCount(verticallyLines);
    else
        m_axisY->setTickCount(2);

    m_axisX->setRange(xBegin, xEnd);
    m_axisY->setRange(yBegin,yEnd);
}

DynamicChart::~DynamicChart()
{
    delete m_series;
}

void DynamicChart::boringFunctionWriteVector(std::vector<SendData<double> > vSendFromServerApp)
{
    vSend.clear();
    for(auto it:vSendFromServerApp)
    {
        vSend.push_back(it);
    }
}

void DynamicChart::handleTimeout()
{
    for(auto it : vSend){
        qreal sizeOfAxisX = plotArea().width();
        qreal pixelOnNumberX = sizeOfAxisX/(xEnd-xBegin);
        m_x =it.getTimeStamp();
        m_y = it.getValue();
        m_series->append(m_x, m_y);
        scroll(pixelOnNumberX, 0);
    }
}


