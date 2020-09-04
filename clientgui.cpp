#include "clientgui.h"

#include <QtWidgets>
#include<QMessageBox>


ClientGui::ClientGui(QWidget *parent)
    : QDialog(parent)
    , hostCombo(new QComboBox)
    , portLineEdit(new QLineEdit)
    , connectButton(new QPushButton(tr("Connect and start reading")))
    , readButton(new QPushButton(tr("Stop")))
{
    portLineEdit->setValidator(new QIntValidator(1,65535,this));

    auto hostLabel = new QLabel(tr("&Server name:"));
    hostLabel->setBuddy(hostCombo);
    auto portLabel = new QLabel(tr("S&erver port:"));
    portLabel->setBuddy(portLineEdit);
    statusLabel = new QLabel;
    setStatusLabel("This examples requires that you run the "
                   "Scada Server as well.");
    connectButton->setDefault(true);
    connectButton->setEnabled(true);

    readButton->setDefault(true);
    readButton->setEnabled(true);


    auto quitButton = new QPushButton(tr("Quit"));

    auto buttonBox = new QDialogButtonBox;
    buttonBox->addButton(readButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(connectButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(readButton, &QAbstractButton::clicked,this, &ClientGui::startReadData);
    connect(connectButton, &QAbstractButton::clicked,this, &ClientGui::changeIpPort);
    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);

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
    PortNumberSlot=PortNumberSlotFromService;
}

void ClientGui::setStatusLabel(std::string sLabel)
{
    const char * qstr = sLabel.c_str();
    statusLabel->setText(tr(qstr));
}

void ClientGui::messageB(std::string mesg)
{
    QString QMesg = QString::fromStdString(mesg);
    QMessageBox::information(this,tr("Scada Client"),QMesg);
}




void ClientGui::changeIpPort()
{
    if( !hostCombo->currentText().isEmpty() && !portLineEdit->text().isEmpty() )
    {
        *IpAdressSlot = hostCombo->currentText();
        QString konefka=*IpAdressSlot;
        *PortNumberSlot = portLineEdit->text();
        konefka=*PortNumberSlot;
        emit changedIpPort();
    }
}



