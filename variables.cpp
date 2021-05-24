#include "variables.h"

Variables::Variables()
{

}

string Variables::getTipo() const
{
    return tipo;
}

void Variables::setTipo(const string &value)
{
    tipo = value;
}

string Variables::getVariable() const
{
    return variable;
}

void Variables::setVariable(const string &value)
{
    variable = value;
}

bool Variables::getUsada() const
{
    return usada;
}

void Variables::setUsada(bool value)
{
    usada = value;
}
