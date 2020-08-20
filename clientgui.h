#ifndef CLIENTGUI_H
#define CLIENTGUI_H


#include <QObject>
#include <QDialog>

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QGuiApplication>

#include <QtWidgets>

#include <string>
#include <vector>
#include <iostream>
QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE


class ClientGui: public QDialog
{
    Q_OBJECT

public:
    //ClientGui();
    explicit ClientGui(QWidget *parent = nullptr);

    void fromHostVectorToHostCombo(std::vector<std::string> hostVector);
    void setIpPortSlot( QString *IpAdressSlotFromService,QString *PortNumberSlotFromServic);
signals:
    void changedIpPort();

private slots:
    void changeIpPort();
//    void changePortLine();
    //    void changeIPAdressString();



private:
    QComboBox *hostCombo = nullptr;
    QLineEdit *portLineEdit = nullptr;
    QLabel *statusLabel = nullptr;
    QPushButton *connectButton = nullptr;
    QString aaa;


    //To change ip adress
    QString *IpAdressSlot;
    QString *PortNumberSlot;

};

#endif // CLIENTGUI_H



