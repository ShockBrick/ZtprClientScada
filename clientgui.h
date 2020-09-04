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

//ClientService Gui
/** Klasa tworzy interfejs graficzny służący do tworzenia połączenia sieciowego.**/
class ClientGui: public QDialog
{
    Q_OBJECT

public:
    /** \brief Konstruktor tworzączy całą grafikę służącą do komunikacji sieciowej.
     *
     * Oraz tworzy połączenia między slotami i syganłami w tej klasie.
     *
     */
    explicit ClientGui(QWidget *parent = nullptr);
    /** \brief Funkcja dodaje wartości do hostCombo.
     *
     * @param hostVector Z tego wektora pobierane są wartości dla hostCombo.
     *
     */
    void fromHostVectorToHostCombo(std::vector<std::string> hostVector);

    /** \brief Funkcja przypisuje zmienne IpAdressSlot i PortNumberSlot .
     *
     * Funkcja jest wykorzystywana aby wskaźniki IpAdressSlot i PortNumberSlot wskazywały na te same zmienne co wskaźniki wykorzystywane w klasie ClientService.
     *
     */
    void setIpPortSlot( QString *IpAdressSlotFromService,QString *PortNumberSlotFromServic);

    /** \brief Funkcja służy do ustawiania co ma wskazywac etykieta statusLabel.
     *
     *
     */
    void setStatusLabel(std::string sLabel);
    /** \brief Funkcja służy wyswietlenia okna Message.
     *
     * @param mesg Wiadomość jaka ma być wyświetlona.
     */
    void messageB(std::string mesg);




signals:
    /** \brief Sygnał informuje o wykonaniu funkcji changeIpPort().
     *
     *
     */
    void changedIpPort();
    /** \brief Sygnał, który jest  wysyłany po kliknięciu użytkownika przycisku.
     *
     * Informuje o rozkazie zatrzymania transmisji.
     * Nazwa myląca.
     */
    void startReadData();

private slots:
    /** \brief Funkcja aktualizuje *IpAdressSlot i *PortNumberSlot.
     *
     * Pobiera dane z interfejsu użytkownika i wpisuje je do zmiennych.
     * Po wykonaniu uruchamia sygnał changedIpPort(). Który jest rozkazem rozpoczecia transmisji.
     */
    void changeIpPort();

private:
    QComboBox *hostCombo = nullptr;/**< \brief Obiekt typu QComboBox, zawiera dostępne adresy Ip i hosty.*/
    QLineEdit *portLineEdit = nullptr;/**< \brief Obiekt typu QLineEdit, wpisuje się do niego numer portu serwera z którym klient chce się połączyć.*/
    QLabel *statusLabel = nullptr;/**< \brief Obiekt typu QLabel, wyświetla informacjie o statusie połączenia*/
    QPushButton *connectButton = nullptr;/**< \brief Obiekt typu QPushButton, służy do zawierania połączenia.*/
    QPushButton *readButton = nullptr;/**< \brief Obiekt typu QPushButton, służy do zatrzymania transmisji.*/
    QString aaa;

    //To change ip adress
    QString *IpAdressSlot;/**< \brief Obiekt typu QString, zawiera adres Ip*/
    QString *PortNumberSlot;/**< \brief Obiekt typu QString, zawiera numer portu serwera.*/

};

#endif // CLIENTGUI_H



