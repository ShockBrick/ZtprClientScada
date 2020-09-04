#include "mainwindow.h"

#include <QAction>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include <QChartView>
#include <QDockWidget>

Q_DECLARE_METATYPE(QDockWidget::DockWidgetFeatures)

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
    ,updateChart(new QPushButton(tr("Update chart")))
    ,openClienService(new QPushButton(tr("Connect to server")))
    ,colorOfMarkerComboBox(new QComboBox)
    ,sizeOfAxisXLineEdit(new QLineEdit )
    ,sizeOfAxisYLineEdit(new QLineEdit)
    ,numberOfVerticalLinesLineEdit(new QLineEdit)
    ,numberOfHorizontalLinesLineEdit(new QLineEdit)
    ,equationLineEdit(new QLineEdit)
    ,equationActive(new QPushButton(tr("Process data \n using the equation")))
{
    pom="sluzy do nowego commitu";
    wdg = new QWidget(this);
    vlay = new QGridLayout(wdg);

    colorOfMarkerLabel = new QLabel(tr("&Select a marker colour "));
    colorOfMarkerLabel->setBuddy(colorOfMarkerComboBox);
    QString helpColor;
    helpColor="black";
    colorOfMarkerComboBox->addItem(helpColor);
    helpColor="cyan";
    colorOfMarkerComboBox->addItem(helpColor);
    helpColor="red";
    colorOfMarkerComboBox->addItem(helpColor);
    helpColor="dark red";
    colorOfMarkerComboBox->addItem(helpColor);
    helpColor="magenta";
    colorOfMarkerComboBox->addItem(helpColor);
    helpColor="green";
    colorOfMarkerComboBox->addItem(helpColor);
    helpColor="yellow";
    colorOfMarkerComboBox->addItem(helpColor);
    helpColor="dark yellow";
    colorOfMarkerComboBox->addItem(helpColor);
    helpColor="blue";
    colorOfMarkerComboBox->addItem(helpColor);
    helpColor="gray";

    colorOfMarkerComboBox->addItem(helpColor);
    sizeOfAxisXLabel = new QLabel(tr("&Select the x-axis range"));
    sizeOfAxisXLabel->setBuddy(sizeOfAxisXLineEdit);
    sizeOfAxisYLabel = new QLabel(tr("&Select the y-axis range"));
    sizeOfAxisYLabel->setBuddy(sizeOfAxisYLineEdit);
    numberOfVerticalLinesLabel = new QLabel(tr("&Select the number of vertical lines"));
    numberOfVerticalLinesLabel->setBuddy(numberOfVerticalLinesLineEdit);
    numberOfHorizontalLinesLabel = new QLabel(tr("&Select the number of horizontal lines"));
    numberOfHorizontalLinesLabel->setBuddy(numberOfHorizontalLinesLineEdit);
    equationLabel = new QLabel(tr("&Give the equation"));
    equationLabel->setBuddy(equationLineEdit);

    chart = new DynamicChart;
    chart->setTitle("Data");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    openClienService->setDefault(true);
    openClienService->setEnabled(true);

    auto quitButton = new QPushButton(tr("Quit"));
    auto buttonBox1 = new QDialogButtonBox;
    auto buttonBox2 = new QDialogButtonBox;
    buttonBox2->addButton(updateChart, QDialogButtonBox::ActionRole);
    buttonBox2->addButton(equationActive, QDialogButtonBox::ActionRole);
    buttonBox1->addButton(openClienService, QDialogButtonBox::ActionRole);
    buttonBox1->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(updateChart, &QAbstractButton::clicked,this, &MainWindow::changeChart);
    connect(equationActive, &QAbstractButton::clicked,this, &MainWindow::startSolveEquation);
    connect(openClienService, &QAbstractButton::clicked,this, &MainWindow::openService);
    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);

    QLabel *parserDescription = new QLabel();
    parserDescription->setText("The formula may contain numbers, \"*\", \"/\", \"+\" and \"-\".\n By means of \"x\" we present in the formula a variable downloaded from the server.");


    QLabel *help = new QLabel();
    help->setText("The formula may contain numbers, \"*\", \"/\", \"+\" and \"-\".\n By means of \"x\" we present in the formula a variable downloaded from the server.");



    vlay->addWidget(colorOfMarkerLabel,1,0);
    vlay->addWidget(colorOfMarkerComboBox,2,0);
    vlay->addWidget(sizeOfAxisXLabel,1,1);
    vlay->addWidget(sizeOfAxisXLineEdit,2,1);
    vlay->addWidget(sizeOfAxisYLabel,1,2);
    vlay->addWidget(sizeOfAxisYLineEdit,2,2);
    vlay->addWidget(numberOfVerticalLinesLabel,1,3);
    vlay->addWidget(numberOfVerticalLinesLineEdit,2,3);
    vlay->addWidget(numberOfHorizontalLinesLabel,1,4);
    vlay->addWidget(numberOfHorizontalLinesLineEdit,2,4);
    vlay->addWidget(equationLabel,1,5);
    vlay->addWidget(equationLineEdit,2,5);
    vlay->addWidget(parserDescription,0,5);


    vlay->addWidget(buttonBox1,0,6);
    vlay->addWidget(buttonBox2,1,6);
    vlay->addWidget(chartView,3,0,5,6);

    wdg->setLayout(vlay);
    setCentralWidget(wdg);

    setObjectName("MainWindow");
    setWindowTitle("Qt Main Window");
    setWindowTitle(QGuiApplication::applicationDisplayName());

}

MainWindow::~MainWindow()
{
 delete chart;
}

void MainWindow::boringFunctionWriteVector(std::vector<SendData<double> > vSendFromServerApp)
{
    vSend.clear();
    for(auto it:vSendFromServerApp)
    {
        vSend.push_back(it);
    }
}

std::string MainWindow::getEquation()
{
    return equation;
}

void MainWindow::emitSignalsToDynamicChart()
{
    chart->boringFunctionWriteVector(vSend);
    emit chart->updateChart();
}

void MainWindow::startSolveEquation()
{
    equation=equationLineEdit->text().toUtf8().constData();
    emit signalStartSolveEquation();

}

void MainWindow::changeChart()
{
    std::string xpom1= sizeOfAxisXLineEdit->text().toUtf8().constData();
    std::string ypom1= sizeOfAxisYLineEdit->text().toUtf8().constData();

    double xpom1d ;
    double ypom1d;
    try {
        xpom1d = std::stod(xpom1);
        ypom1d = std::stod(ypom1);
    } catch (...) {
        xpom1d = 10;
        ypom1d = 1;
    }

    double xpom2d ;
    double ypom2d;

    if(vSend.size()>0){
        ypom2d = vSend[vSend.size()-1].getValue();
        xpom2d = vSend[vSend.size()-1].getTimeStamp();
    }
    else
    {
        xpom2d = 0;
        ypom2d = 0;
    }

    int xpom3;
    int ypom3;
    try {
        xpom3 = std::stoi(numberOfVerticalLinesLineEdit->text().toUtf8().constData());
        ypom3 = std::stoi(numberOfHorizontalLinesLineEdit->text().toUtf8().constData());
    } catch (...) {
        xpom3 = 2;
        ypom3 = 10;
    }
    delete chart;
    chart=new DynamicChart(colorOfMarkerComboBox->currentText().toUtf8().constData(),xpom1d,ypom1d,xpom2d,ypom2d,ypom3,xpom3);
    chart->setTitle("Data");
    chart->legend()->hide();
    chart->setAnimationOptions(QChart::AllAnimations);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    vlay->addWidget(chartView,3,0,5,6);
    wdg->setLayout(vlay);
}

