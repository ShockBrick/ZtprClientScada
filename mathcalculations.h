#ifndef MATHCALCULATIONS_H
#define MATHCALCULATIONS_H
#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <exception>
/** Klasa abstrakcyjna.**/
class MathCalculations
{
public:
    virtual void makeQueue( )=0;//będę musiał za każdym razem tworzyć bo w funkcji countResult czyszczę equationRPN
    virtual void setEquatequationInfix(std::string pom)=0;
    virtual double countResult(double x)=0;
    std::string pommmmmm;
};

#endif // MATHCALCULATIONS_H
