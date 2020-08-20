#ifndef CLIENTSERVICE_H
#define CLIENTSERVICE_H

#include <QDataStream>
#include <QObject>
#include<vector>
#include <QtNetwork>
#include <QTcpSocket>
#include<senddata.h>
#include <clientgui.h>

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE


class ClientService: public QObject
{
    Q_OBJECT

public:
    ClientService();// explicit Client(QWidget *parent = nullptr);





private slots:
    void connectToServer();
    void sessionOpened();
    void displayError(QAbstractSocket::SocketError socketError);
    //    void requestNewFortune();
    void readVectorOfData();
    //    void enableGetFortuneButton();


private:
    std::vector<std::string> hostCombo ={};//wektor dostepnych hostow, adresy IP
    std::string portLineEdit = {};//pole do wpisania numeru portu
    std::string statusLabel = {};
  //  QPushButton *getFortuneButton = nullptr;

    QTcpSocket *tcpSocket = nullptr;
    QDataStream in;
    QString currentFortune;

    QNetworkSession *networkSession = nullptr;

    ClientGui guiC;

    //To change ip adress
    QString *IpAdressSlot=new QString;
    QString *PortNumberSlot=new QString;


    // vector of data which is take from server
//    std::vector <SendData<double>> vSend ;
};

#endif // CLIENTSERVICE_H
