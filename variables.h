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

private:
    string tipo;
    string variable;
};

#endif // VARIABLES_H
