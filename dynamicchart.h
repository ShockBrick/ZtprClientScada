#ifndef DYNAMICCHART_H
#define DYNAMICCHART_H

#include <senddata.h>
#include <vector>
#include <string>

#include <QtCharts/QChart>
#include <QtCore/QTimer>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE


/** Klasa tworzy wykres wyświetlający ciągle dane przychodzące z serwera.**/
class DynamicChart:public QChart
{
    Q_OBJECT
public:
    /** \brief Konstruktor tworzący wykres podstatwowy.
     *
     */
    DynamicChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    /** \brief Konstruktor tworzący wykres sparametryzowany przez użytkownika.
     *
     * @param PenColor Kolor markera, który oznacza na wykresie dane.
     * @param xHalfRange1 Określa połowę zakres na osi x jaki użytkownik żąda.
     * @param yHalfRange1 Określa połowę zakres na osi y jaki użytkownik żąda
     *@param xValueNow Określa wartość jaką w tej chwili w osi x przyjmują dane.
     * @param yValueNow Określa wartość jaką w tej chwili w osi y przyjmują dane.
     * @param horizontallyLines Określa liczbę linii jaka ma być na wykresie w pionie.
     * @param verticallyLines Określa liczbę linii jaka ma być na wykresie w poziomie.
     */
    DynamicChart(std::string PenColor,double xHalfRange1=(10),double yHalfRange1=(1),double xValueNow=(0),double yValueNow=(0),int horizontallyLines=(2),int verticallyLines=(2), QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    virtual ~DynamicChart();


    /** \brief Funkcja zapisuje dane z zewnętrznego wektora do wektora vSend.
     *
     *
     */
    void boringFunctionWriteVector( std::vector <SendData<double>> vSendFromServerApp);

signals:

    /** \brief Sygnał przychodzący oznaczający rozkaz wyświetlenia nowych danych.
     *
     *
     */
    void updateChart();

public slots:

    /** \brief Funkcja dodaje nowe punkty z vSend do wykresu.
     *
     *
     */
    void handleTimeout();

private:
    std::vector <SendData<double>> vSend ;/**< \brief Wektor danych, w którym zapisuje się dane pobrane z serwera.*/



    QSplineSeries *m_series;/**< \brief Obiekt typu  QSplineSeries, oznacza serie danych.*/

    QValueAxis *m_axisX;/**< \brief Obiekt typu  QValueAxis, oznacza oś X.*/
    QValueAxis *m_axisY;/**< \brief Obiekt typu  QValueAxis, oznacza oś Y.*/

    qreal m_x;/**< \brief Zmienna oznaczająca współrzędną x punktu dodawanego do wykresu.*/
    qreal m_y;/**< \brief Zmienna oznaczająca współrzędną y punktu dodawanego do wykresu.*/


    //range X
    qreal xBegin;/**< \brief Zmienna oznacza początek zakresy wyświetlania w osi x.*/
    qreal xEnd;/**< \brief Zmienna oznacza koniec zakresy wyświetlania w osi x.*/

    //range Y
    qreal yBegin;/**< \brief Zmienna oznacza początek zakresy wyświetlania w osi y.*/
    qreal yEnd;/**< \brief Zmienna oznacza koniec zakresy wyświetlania w osi y.*/

// chart individualisation
    double xHalfRange;/**< \brief Zmienna oznaczająca połwę zakresu jaki w osi x życzy sobie użytkownik.*/
    double yHalfRange;/**< \brief Zmienna oznaczająca połwę zakresu jaki w osi y życzy sobie użytkownik.*/

    QPen green;/**< \brief Obiekt typu   QPen, oznacza on marker.*/
    std::string pommmmmm;
};

#endif // DYNAMICCHART_H
