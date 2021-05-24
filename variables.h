#ifndef VARIABLES_H
#define VARIABLES_H
#include <iostream>

using namespace std;

class Variables
{
public:
    Variables();

    string getTipo() const;
    void setTipo(const string &value);

    string getVariable() const;
    void setVariable(const string &value);

    bool getUsada() const;
    void setUsada(bool value);

private:
    string tipo;
    string variable;
    bool usada;
};

#endif // VARIABLES_H
