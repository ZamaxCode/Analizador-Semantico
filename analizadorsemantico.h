#ifndef ANALIZADORSEMANTICO_H
#define ANALIZADORSEMANTICO_H
#include <variables.h>
#include <vector>

class AnalizadorSemantico
{
public:
    AnalizadorSemantico();
    bool declararVariable(const string tipo, const string var);

private:
    vector<Variables> varArray;
};

#endif // ANALIZADORSEMANTICO_H
