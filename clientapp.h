#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include <string>
#include<iostream>
#include<senddata.h>
#include <clientservice.h>
#include <vector>


#include <clientservice.h>
#include<senddata.h>
#include <mainwindow.h>
#include <parser.h>
#include <mathcalculations.h>


/** Klasa tworzy główną aplikacją, steruje pozostałymi klasami.
Dziedziczy po klasie ClientService.
**/
class ClientApp: public ClientService
{
    Q_OBJECT
public:
    /** \brief Konstruktor tworzączy połączenia między slotami i sygnałami.
     *
     * Oprócz tego wyświetla mainWin, oraz
     * przypisuje do wskaźnika *mathIndicator obiekt typu Parser.
     * Wywołuje też kostruktor klasy ClientService.
     *
     */
    ClientApp();

signals:

    /** \brief Sygnał który mówi o wykonaniu funkcij: updateMainWindowVector()
     *
     */
    void goToMainWindowWithData();

private slots:
    /** \brief Funkcja aktualizuje zmienną equation.
     *
     * Pobiera dane z interfejsu użytkownika i aktualizuje wzór.
     *
     */
   void StartPars();

public slots:
   /** \brief Funkcja ta aktualizuje wektor danych w mainWindow i emituje sygnał o tym.
    *
    * Oprócz tego przed wysłaniem wektora danych do mainWin wykorzystuje obiekt typu Pareser do obrobienia danych.
    * @see  goToMainWindowWithData()
    *
    */
     void updateMainWindowVector();

private:
     MainWindow mainWin;/**< \brief Obiekt typu MainWindow, służy do wyświetlania danych*/
     Parser pars;/**< \brief Obiekt typu Parser, służy do obrobienia dostarczonych danych.*/
     MathCalculations *mathIndicator;/**< \brief Obiekt typu  MathCalculations, służy jako wskaźnik do pars.*/
     std::string equation{"x"};/**< \brief Zmienna equation zawiera wzór podany przez użytkownika do obrobienia danych przez parser*/
std::string pom;
};

#endif // CLIENTAPP_H
