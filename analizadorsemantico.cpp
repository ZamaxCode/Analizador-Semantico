#include "analizadorsemantico.h"

AnalizadorSemantico::AnalizadorSemantico()
{

}

bool AnalizadorSemantico::declararVariable(const string tipo, const string var)
{
    for(size_t i(0);i<varArray.size();++i)
    {
        if(var==varArray.at(i).getVariable())
            return true;
    }
    Variables v;
    v.setVariable(var);
    v.setTipo(tipo);
    return false;
}
