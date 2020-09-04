#include <QCoreApplication>

#include <QApplication>


#include <clientapp.h>
#include <dynamicchart.h>

#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <mainwindow.h>
QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    auto pom="sluzy do nowego commitu";
    QApplication app(argc, argv);
    ClientApp a;
    return app.exec();
}

