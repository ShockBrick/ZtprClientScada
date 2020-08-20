#include "clientgui.h"







//ClientGui::ClientGui()
//{

//}

ClientGui::ClientGui(QWidget *parent)
    : QDialog(parent)
    , hostCombo(new QComboBox)
    , portLineEdit(new QLineEdit)
    , connectButton(new QPushButton(tr("Connect")))
{
    portLineEdit->setValidator(new QIntValidator(1,65535,this));

    auto hostLabel = new QLabel(tr("&Server name:"));
    hostLabel->setBuddy(hostCombo);
    auto portLabel = new QLabel(tr("S&erver port:"));
    portLabel->setBuddy(portLineEdit);
    statusLabel = new QLabel(tr("This examples requires that you run the "
                                "Scada Server as well."));

    connectButton->setDefault(true);
    connectButton->setEnabled(true);

    auto quitButton = new QPushButton(tr("Quit"));

    auto buttonBox = new QDialogButtonBox;
    buttonBox->addButton(connectButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(connectButton, &QAbstractButton::clicked,this, &ClientGui::changeIpPort);
    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
//    connect(hostCombo, &QComboBox::editTextChanged, this, &ClientGui::changeIPAdressCombo);
//    connect(portLineEdit, &QLineEdit::textChanged,this, &ClientGui::changePortLine);
//    connect(konefka,SIGNAL(textChanged(QString)), this, &ClientGui::changeIPAdressString);
//    connect(portLineEdit, &QLineEdit::textChanged, this, &Client::enableGetFortuneButton);
//    connect(getFortuneButton, &QAbstractButton::clicked,this, &Client::requestNewFortune);

////! [2] //! [3]
//    connect(tcpSocket, &QIODevice::readyRead, this, &Client::readFortune);
////! [2] //! [4]
//    connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
////! [3]
//            this, &Client::displayError);
////! [4]

    QGridLayout *mainLayout = nullptr;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        auto outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        auto outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        auto groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
        mainLayout = new QGridLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout->addLayout(outerHorizontalLayout);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    } else {
        mainLayout = new QGridLayout(this);
    }
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostCombo, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLineEdit, 1, 1);
    mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 3, 0, 1, 2);

    setWindowTitle(QGuiApplication::applicationDisplayName());
    portLineEdit->setFocus();
}

void ClientGui::fromHostVectorToHostCombo(std::vector<std::string> hostVector)
{
    hostCombo->setEditable(true);
    for(auto host:hostVector)
    {
        QString helpVariable = QString::fromStdString(host);
        hostCombo->addItem(helpVariable);
    }

}

void ClientGui::setIpPortSlot( QString *IpAdressSlotFromService,QString *PortNumberSlotFromService)
{
    IpAdressSlot=IpAdressSlotFromService;
       std::cout<<"gui IP: "<<IpAdressSlot<<std::endl;
       PortNumberSlot=PortNumberSlotFromService;
       std::cout<<"gui Port: "<<PortNumberSlot<<std::endl;
}




void ClientGui::changeIpPort()
{

    if( !hostCombo->currentText().isEmpty() && !portLineEdit->text().isEmpty() )
    {
        *IpAdressSlot = hostCombo->currentText();
        QString konefka=*IpAdressSlot;
        std::cout<<"IPAdresss"<<konefka.toUtf8().constData()<<std::endl;
        //        *IpAdressSlot = konefka;
        //        *IpAdressSlot = hostCombo->currentText();

        *PortNumberSlot = portLineEdit->text();//.toInt()
        konefka=*PortNumberSlot;
        std::cout<<"Port Number:  "<<konefka.toUtf8().constData()<<std::endl;
        //        *IpAdressSlot = konefka;
        //        *IpAdressSlot = hostCombo->currentText();
        emit changedIpPort();
    }


}



