#include "clientservice.h"

#include <QtNetwork>
#include <QTcpSocket>

ClientService::ClientService()
{
        tcpSocket = new QTcpSocket;
connect(&guiC,&ClientGui::changedIpPort,this,&ClientService::connectToServer);

connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &ClientService::displayError);

connect(tcpSocket, &QIODevice::readyRead, this, &ClientService::readVectorOfData);

//connect(getFortuneButton, &QAbstractButton::clicked,
//        this, &Client::requestNewFortune);

//connect(tcpSocket, &QIODevice::readyRead, this, &Client::readFortune);



















//     connect(IpAdressSlot,textChanged(QString),this, &ClientGui::changeIpPort);
//     connect(IpAdressSlot,textChanged(QString),this, &ClientGui::changeIpPort);

    // find out name of this machine
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty()) {
        hostCombo.push_back(name.toUtf8().constData());
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
        {
            std::string pom1 = name.toUtf8().constData();
            std::string pom2 = domain.toUtf8().constData();
            hostCombo.push_back(pom1 + "." + pom2);
        }
    }

    std::string helpString;
    if (name != QLatin1String("localhost"))
    {
        helpString="";
        helpString=QString("localhost").toUtf8().constData();
        hostCombo.push_back(helpString);}

    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
        {
            helpString="";
            helpString=ipAddressesList.at(i).toString().toUtf8().constData();
            hostCombo.push_back(helpString);
        }
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
        {
            helpString="";
            helpString=ipAddressesList.at(i).toString().toUtf8().constData();
            hostCombo.push_back(helpString);
        }
    }
    //    guiC.fromHostVectorToHostCombo(hostCombo);
    //    guiC.show();
    //   guiC.setIpAdressSlotAdress(IpAdressSlot);


    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);


    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, &QNetworkSession::opened, this, &ClientService::sessionOpened);

//        getFortuneButton->setEnabled(false);

        std::cout<<"Opening network session."<<std::endl;

//        statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    }





    guiC.setIpPortSlot(IpAdressSlot,PortNumberSlot);
    std::cout<<"service IP: "<<IpAdressSlot<<std::endl;//.toUtf8().constData()
    std::cout<<"service Port: "<<PortNumberSlot<<std::endl;//.toUtf8().constData()
    guiC.fromHostVectorToHostCombo(hostCombo);
    guiC.show();

//    std::cout<<IpAdressSlot<<std::endl;
    //    std::cout<<*IpAdressSlot->toUtf8().constData()<<std::endl;
}

void ClientService::connectToServer()
{
    std::cout<<"IP from gui in service: "<<IpAdressSlot->toUtf8().constData()<<std::endl;
    std::cout<<"Port from gui in service: "<<PortNumberSlot->toInt()<<std::endl;

    tcpSocket->abort();
const QString &hostName =IpAdressSlot->toUtf8().constData();
quint16 port =PortNumberSlot->toInt()/*PortNumberSlot->toUtf8().constData()*/;
//, QIODevice::OpenMode openMode = ReadWrite, QAbstractSocket::NetworkLayerProtocol protocol = AnyIPProtocol
    tcpSocket->connectToHost(hostName,port);








}



void ClientService::sessionOpened()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
    std::cout<<"This examples requires that you run the Fortune Server example as well."<<std::endl;
//    statusLabel->setText(tr("This examples requires that you run the "
//                            "Fortune Server example as well."));

//    enableGetFortuneButton();
}

void ClientService::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
         std::cout<<"The host was not found. Please check the "
                    "host name and port settings."<<std::endl;
//        QMessageBox::information(this, tr("Fortune Client"),
//                                 tr("The host was not found. Please check the "
//                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        std::cout<<"The connection was refused by the peer. "
                   "Make sure the fortune server is running, "
                   "and check that the host name and port "
                   "settings are correct."<<std::endl;

//        QMessageBox::information(this, tr("Fortune Client"),
//                                 tr("The connection was refused by the peer. "
//                                    "Make sure the fortune server is running, "
//                                    "and check that the host name and port "
//                                    "settings are correct."));
        break;
    default:
        std::cout<<"The following error occurred: ."<<std::endl<<tcpSocket->errorString().toUtf8().constData()<<std::endl;


//        QMessageBox::information(this, tr("Fortune Client"),
//                                 tr("The following error occurred: %1.")
//                                 .arg(tcpSocket->errorString()));
    }

    //    getFortuneButton->setEnabled(true);
}

void ClientService::readVectorOfData()
{
    in.startTransaction();
std::vector <SendData<double>> vSend ;
    vSend.clear();
    in >> vSend;

    if (!in.commitTransaction())
        return;

//    if (nextFortune == currentFortune) {
//        QTimer::singleShot(0, this, &Client::requestNewFortune);
//        return;
//    }

//    currentFortune = nextFortune;

//    statusLabel->setText(currentFortune);
//    getFortuneButton->setEnabled(true);
    for (auto pojemnik:vSend)
    {
        std::cout<<"Wartosc: "<<pojemnik.getValue()<<"     "<<"Czas: "<<pojemnik.getTimeStamp()<<std::endl;
    }
}

