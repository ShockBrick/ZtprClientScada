#include "clientservice.h"



ClientService::ClientService()
{
    tcpSocket = new QTcpSocket;
    connect(&guiC,&ClientGui::changedIpPort,this,&ClientService::connectToServer);
    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this, &ClientService::displayError);
    connect(tcpSocket, &QIODevice::readyRead, this, &ClientService::readVectorOfData);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&ClientService::connectToServer));
    connect(&guiC,&ClientGui::startReadData, timer, &QTimer::stop);
    connect(&guiC,&ClientGui::startReadData, this, &ClientService::FalseTimerStart);

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

        std::string pom ="Opening network session.";
        guiC.setStatusLabel(pom);
        networkSession->open();
    }
}

ClientService::~ClientService()
{
    delete IpAdressSlot;
    delete PortNumberSlot;
}

void ClientService::ServiceVSendToOtherVector(std::vector<SendData<double> > &vSendOther)
{
    for(auto it : vSend){vSendOther.push_back(it);}
}

void ClientService::voidClientService()
{
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

   guiC.setIpPortSlot(IpAdressSlot,PortNumberSlot);
    guiC.fromHostVectorToHostCombo(hostCombo);
    guiC.show();
}

void ClientService::connectToServer()
{
    tcpSocket->abort();
    const QString &hostName =IpAdressSlot->toUtf8().constData();
    quint16 port =PortNumberSlot->toInt();
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
    std::string pom ="This examples requires that you run the  Scada Server example as well.";
    guiC.setStatusLabel(pom);

}

void ClientService::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
    {
        std::string pom="The host was not found. Please check the "
                        "host name and port settings.";
        guiC.messageB(pom);

        break;}
    case QAbstractSocket::ConnectionRefusedError:
    {
        std::string pom ="The connection was refused by the peer. "
                         "Make sure the fortune server is running, "
                         "and check that the host name and port "
                         "settings are correct.";
        guiC.messageB(pom);
    }
    default:
    {
        std::string pom =std::string("The following error occurred: .") + ("\n") + std::string(tcpSocket->errorString().toUtf8().constData()) + "\n";
        guiC.messageB(pom);
    }
    }
}

void ClientService::readVectorOfData()
{
    if(&QIODevice::isReadable)
    {
        in.startTransaction();
        vSend.clear();
        in >> vSend;

        if (!in.commitTransaction())
            return;

        emit dataWereReceived();
        if(timerStart==false)
        {
            timer->start(5000);
            timerStart=true;
        }
    }
}

void ClientService::FalseTimerStart()
{
    timerStart = false;
}
