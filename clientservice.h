#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H

#include <QDataStream>
#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QTimer>
#include <QIODevice>

#include<vector>
#include<senddata.h>
#include <clientgui.h>
#include<iostream>
#include <string>


QT_BEGIN_NAMESPACE
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE


/** Klasa tworzy klienta służącego do połączenia sieciowego.**/
class ClientService: public QObject
{
    Q_OBJECT

public:
    /** \brief Konstruktor tworzy połączenia między sygnałami i slotami.
     *
     * Oraz tworzy managera konfiguracji sieci.
     *
     */
    ClientService();
    /** \brief Funkcja słuzy do kopiowania wektora danych vSend.
     *
     * @param vSendOther Jest to wektor do którego kopiuje się wektor vSend.
     *
     */

    ~ClientService();
    void ServiceVSendToOtherVector(std::vector <SendData<double>> &vSendOther );



signals:
    /** \brief Sygnał informuje o dotarciu danych z serwera.
     *
     *
     */
    void dataWereReceived();

public slots:
    /** \brief Funkcja słuzy do prześwietlenia sieci i znalezienie dostępnych hostów.
     *
     * Umożliwia też wyświetlenie interfeju graficznego guiC.
     *
     */
    void voidClientService();

private slots:
    /** \brief Funkcja resetuje gniazdo tcp,
     *
     * za pomocą danych z IpAdressSlot i PortNumberSlot
     *
     */
    void connectToServer();
    /** \brief Funkcja tworzy konfiguracje połączenia
     *
     *
     *
     */
    void sessionOpened();
    /** \brief Funkcja wyświetla błędy występujące podczas połączenia.
     *
     *
     *
     */
    void displayError(QAbstractSocket::SocketError socketError);
    /** \brief Funkcja odczytuje z serwera wektor danych.
     *
     *
     *
     */
    void readVectorOfData();
    /** \brief Funkcja zmienia stan zmiennej timerStart na false.
     *
     *
     *
     */
    void FalseTimerStart();

protected:

    // vector of data which is take from server
    std::vector <SendData<double>> vSend ;/**< \brief Wektor danych, w którym zapisuje się dane pobrane z serwera.*/

private:
    QTimer *timer = new QTimer(this);/**< \brief Obiekt typu  QTimer, umożliwiający regularne wysłanie zapytania o dane.*/
    bool timerStart{false};/**< \brief Zmienna przerywająca transmisję danych.*/

    std::vector<std::string> hostCombo ={};/**< \brief Wektor mozliwych hostów.*/


    QTcpSocket *tcpSocket = nullptr;/**< \brief Obiekt typu QTcpSocket, tworzy gniazdo TCP.*/
    QDataStream in;/**< \brief Obiekt typu  QDataStream, strumień, przez który, płyną dane z serwera.*/

    QNetworkSession *networkSession = nullptr;/**< \brief Obiekt typu  QNetworkSession.*/

    ClientGui guiC;/**< \brief Obiekt typu  ClientGui, interfejs graficzny.*/

    //To change ip adress
    QString *IpAdressSlot=new QString;/**< \brief Zmienna zawierająca IP serwer.*/
    QString *PortNumberSlot=new QString;/**< \brief Zmienna zawierająca numer portu serwera.*/



    std::string pommmmmm;
};


#endif // CLIENTSERVICE_H
