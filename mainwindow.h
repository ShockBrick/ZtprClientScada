#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>



#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QGuiApplication>
#include <QtWidgets>


#include <dynamicchart.h>
#include <senddata.h>
#include <vector>
#include <iostream>
#include <string>

#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

QT_CHARTS_USE_NAMESPACE



/** Klasa interfejsu użytkownika, zawiera wykres, interfejs do jego indywidualizacji i przycisk do uruchomienia okna służącego do nawiązania połączenia sieciowego.**/
class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    /** \brief Konstruktor tworzący grafikę interfejsu użytkownika.
     *
     */
    explicit MainWindow(   QWidget *parent = nullptr, Qt::WindowFlags flags = 0);

    ~MainWindow();
    /** \brief Funkcja zapisuje dane z zewnętrznego wekrtora do wektora vSend.
     *
     *
     */
    void boringFunctionWriteVector( std::vector <SendData<double>> vSendFromServerApp);
    /** \brief Funkcja zwraca zmienną equation.
     *
     *
     */
    std::string getEquation();



signals:
    /** \brief Sygnał służący do otwarcia okna służącego do parametryzacji i utworzenia połączenia sieciowego.
     *
     *
     */
    void openService();
    /** \brief Sygnał oznaczający rozkaz wykonywania przetwarzania danych przychodzących z serwera za pomocą parsera.
     *
     *
     */
    void signalStartSolveEquation();

public slots:
    /** \brief Funkcja wysyła wektor vSend do wykresu (*chart) oraz wysyła sygnał do wykresu aby się aktualizował.
     *
     *"emit chart->updateChart()"
     * @see updateChart()
     */
    void emitSignalsToDynamicChart();
    /** \brief Funkcja zapisuje z interfejsu użytkownika wzór do zmiennej equation i emituje sygnał signalStartSolveEquation().
     *
     *
     */
    void startSolveEquation();
    /** \brief Funkcja ta niszczy obecny wykres i tworzy nowy sparametryzowany przez użytkownika.
     *
     *
     */
    void changeChart();

private:
    QPushButton *updateChart = nullptr;/**< \brief Obiekt typu QPushButton, służy do wywoływania funkcji changeChart().*/
    QPushButton *openClienService = nullptr;/**< \brief Obiekt typu QPushButton, służy do wywoływania funkcji  openService().*/

    DynamicChart *chart;/**< \brief Obiekt typu  DynamicChart, tworzy wykres danych.*/
    std::vector <SendData<double>> vSend ;/**< \brief Wektor danych, w którym zapisuje się dane pobrane z serwera.*/



    //chart individualisation
    QLabel *colorOfMarkerLabel = nullptr;/**< \brief Obiekt typu  QLabel, opisujący wybór koloru markera.*/
    QComboBox *colorOfMarkerComboBox = nullptr;/**< \brief Obiekt typu QComboBox, umożliwia wybór koloru markera.*/

    QLabel *sizeOfAxisXLabel = nullptr;/**< \brief Obiekt typu  QLabel, opisujący pole do wpisywania zakresu osi X.*/
    QLineEdit *sizeOfAxisXLineEdit = nullptr;/**< \brief Obiekt typu QLineEdit, umożliwia wpisanie zakresu osi X.*/

    QLabel *sizeOfAxisYLabel = nullptr;/**< \brief Obiekt typu  QLabel, opisujący pole do wpisywania zakresu osi Y.*/
    QLineEdit *sizeOfAxisYLineEdit = nullptr;/**< \brief Obiekt typu QLineEdit, umożliwia wpisanie zakresu osi Y.*/

    QLabel *numberOfVerticalLinesLabel = nullptr;/**< \brief Obiekt typu  QLabel, opisujący pole do wpisania ilości linii poziomych na wykresie.*/
    QLineEdit *numberOfVerticalLinesLineEdit = nullptr;/**< \brief Obiekt typu QLineEdit, umożliwia wpisanie ilości linii poziomych na wykresie.*/

    QLabel *numberOfHorizontalLinesLabel = nullptr;/**< \brief Obiekt typu  QLabel, opisujący pole do wpisania ilości linii pionowych na wykresie.*/
    QLineEdit *numberOfHorizontalLinesLineEdit = nullptr;/**< \brief Obiekt typu QLineEdit, umożliwia wpisanie ilości linii pionowych na wykresie.*/

    QWidget * wdg;/**< \brief Obiekt typu  QWidget, obiekt, który zwiera wszystkie obiekty będące na wyświetlonym oknie.*/
    QGridLayout *vlay ;/**< \brief Obiekt typu  QLabel, opisujący pole do wstawienia wzoru.*/

    //Parser
    QLabel *equationLabel = nullptr;/**< \brief Obiekt typu  QLabel, opisujący pole do wstawienia wzoru.*/
    QLineEdit *equationLineEdit = nullptr;/**< \brief Obiekt typu  QLineEdit, umożliwiający wstawienie wzoru.*/
    QPushButton *equationActive = nullptr;/**< \brief Obiekt typu QPushButton, służy do wywoływania funkcji startSolveEquation().*/
    std::string equation;/**< \brief Zmienna equation zawiera wzór podany przez użytkownika do obrobienia danych przez parser*/

};

#endif // MAINWINDOW_H
