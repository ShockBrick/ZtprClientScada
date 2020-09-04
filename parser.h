#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <exception>

#include <mathcalculations.h>
/** Klasa pozwala na przetworzenie danych. Klasa dziedziczy po klasie abstrakcyjnej MathCalculations**/
class Parser: public MathCalculations
{
public:

    /** \brief Funkcja konwertuje wyrażenie matematyczne zapisane w sposób konwencjonalny na ONP.
     *
     *Wzór zapisany w zmiennej equationInfix funkcja ta przetwarza i zapisuje w equationRPN.
     *
     *
     */
    void makeQueue( );//będę musiał za każdym razem tworzyć bo w funkcji countResult czyszczę equationRPN
    /** \brief Funkcja zapisuje zmienną equationInfix.
     *
     *@param pom Zmienna pom jest zapisywana w zmiennej equationInfix.
     *
     *
     */
    void setEquatequationInfix(std::string pom);
    /** \brief Funkcja oblicza wynik wyrażenia podanego w equationRPN.
     *
     *@param x Zmienna ta reprezentuje argument funkcji.
     * @return Funkcja zwraca wartość wyrażenia będącego w equationInfix.
     *
     */
    double countResult(double x);

private:

    std::string equationInfix;/**< \brief Zmienna equationInfix zawiera wzór podany przez użytkownika  do przetworzenia danych przez parser.*/
    std::stack<double> digits;/**< \brief Stos zawierający liczby podczas obliczani w funkcji countResult(double x). */
    std::stack<std::string> operators;/**< \brief Stos zawierający operatory podczas obliczani w funkcji countResult(double x). */
    std::queue<std::string> equationRPN;/**< \brief Kolejka zawierająca wyrażenie w formie ONP.*/

};

#endif // PARSER_H
