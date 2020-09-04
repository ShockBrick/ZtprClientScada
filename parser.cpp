#include "parser.h"



void Parser::makeQueue()
{

    while(equationRPN.empty()!=true)equationRPN.pop();
    while(operators.empty()!=true)operators.pop();

    std::string pom;
    for (auto it:equationInfix)
    {
        if(it>='0' && it<='9')
        {
            if(pom!="x")
                pom=pom+it;
        }
        else if(it=='*')
        {
            equationRPN.push(pom);
            pom="";
            if(operators.empty()!=true){
                while(operators.empty()!=true && (operators.top()=="/" ||operators.top()=="*") )
                {
                    equationRPN.push(operators.top());
                    operators.pop();
                }

                operators.push("*");
            }
            else
                operators.push("*");
        }
        else if(it=='/')
        {
            equationRPN.push(pom);
            pom="";
            if(operators.empty()!=true){
                while(operators.empty()!=true && (operators.top()=="/" ||operators.top()=="*") )
                {
                    equationRPN.push(operators.top());
                    operators.pop();
                }

                operators.push("/");
            }
            else
                operators.push("/");

            //std::cout<< "jestem w /"<<std::endl;
        }
        else if(it=='+')
        {
            equationRPN.push(pom);
            pom="";
            if(operators.empty()!=true){
                while(operators.empty()!=true && (operators.top()=="/" ||operators.top()=="*"||operators.top()=="+"||operators.top()=="-") )
                {
                    equationRPN.push(operators.top());
                    operators.pop();
                }

                operators.push("+");
            }
            else
                operators.push("+");
        }
        else if(it=='-')
        {
            equationRPN.push(pom);
            pom="";

            if(operators.empty()!=true){
                while(operators.empty()!=true &&(operators.top()=="/" ||operators.top()=="*"||operators.top()=="+"||operators.top()=="-"))
                {
                    equationRPN.push(operators.top());
                    operators.pop();
                }

                operators.push("-");
            }
            else
                operators.push("-");
        }
        else if(it=='x')
        {
            pom="x";
        }
    }

    equationRPN.push(pom);

    while(operators.empty()!=true)
    {
        equationRPN.push(operators.top());
        operators.pop();
    }
}


void Parser::setEquatequationInfix(std::string pom)
{
    equationInfix=pom;
}

double Parser::countResult(double x)
{
    try
    {
        while(equationRPN.empty()!=true)
        {
            if(equationRPN.front()=="*")
            {
                double pom1=digits.top();
                digits.pop();
                double pom2=digits.top();
                digits.pop();
                equationRPN.pop();
                double result=pom2*pom1;
                digits.push(result);
            }
            else if(equationRPN.front()=="/")
            {
                double pom1=digits.top();
                digits.pop();
                double pom2=digits.top();
                digits.pop();
                equationRPN.pop();
                double result=pom2/pom1;
                digits.push(result);
            }
            else if(equationRPN.front()=="+")
            {
                double pom1=digits.top();
                digits.pop();
                double pom2=digits.top();
                digits.pop();
                equationRPN.pop();
                double result=pom2+pom1;
                digits.push(result);
            }
            else if(equationRPN.front()=="-")
            {
                double pom1=digits.top();
                digits.pop();
                double pom2=digits.top();
                digits.pop();
                equationRPN.pop();
                double result=pom2-pom1;
                digits.push(result);
            }
            else if(equationRPN.front()=="x")
            {
                digits.push(x);
                equationRPN.pop();
            }
            else
            {
                digits.push(std::stoi(equationRPN.front()));
                equationRPN.pop();
            }
        }

        return digits.top();
    }
    catch (...) {
        std::cout<<"Możliwe że podałeś zły wzór!!!!!!!!!!!!!"<<std::endl;
        return x;
    }
}
