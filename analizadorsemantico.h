#ifndef ANALIZADORSEMANTICO_H
#define ANALIZADORSEMANTICO_H
#define VarSintax "[a-zA-Z]([a-zA-Z]|\\d|_)*"
#define NumSintax "[+-]?(\\d*[.])?\\d+"
#include <variables.h>
#include <vector>
#include <iostream>
#include <regex>

using namespace std;

class AnalizadorSemantico
{
public:
    AnalizadorSemantico();
    bool declararVariable(const string lineCode);
    bool checarExistencia(const string v1, const string v2, const string v3);

private:
    vector<Variables> varArray;
};

#endif // ANALIZADORSEMANTICO_H
