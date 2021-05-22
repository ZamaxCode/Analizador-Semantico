#include <iostream>
#include <fstream>
#include <analizadorsintactico.h>
#include <analizadorsemantico.h>

using namespace std;

int main()
{
    fstream code;
    AnalizadorSintactico SIN;
    AnalizadorSemantico SEM;
    string codeName, lineCode, lineBefore="", lineBeBefor="";
    int cont=1, contLlaves=0, contDo=0;
    bool open=false;
    bool noneError=true;
    do{
        cout<<"Escriba el nombre del archivo y su extension: ";
        getline(cin, codeName);
        code.open(codeName, ios::in);
        if(code.good())
            open=true;
        else
            cout<<"El archivo no se encontro, intente de nuevo"<<endl;
    }while(!open);
    cout<<"Archivo abierto"<<endl;

    while(!code.eof())
    {
        getline(code, lineCode,'\n');
        cout<<cont<<"\t"<<lineCode<<endl;
        ++cont;
    }
    cont=1;
    code.close();

    code.open(codeName, ios::in);

    while(!code.eof())
    {
        bool error;
        getline(code, lineCode,'\n');
        if(SIN.sintaxAssign(lineCode))
            error=false;
        else
            if(SIN.sintaxCin(lineCode))
            error=false;
            else
                if(SIN.sintaxCout(lineCode))
                    error=false;
                else
                    if(SIN.sintaxFor(lineCode))
                        error=false;
                    else
                        if(SIN.sintaxIf(lineCode))
                        {
                            error=false;
                        }
                        else
                            if(SIN.sintaxElse(lineCode))
                            {
                                if(SIN.sintaxBracketClose(lineBefore)||SIN.sintaxIf(lineBeBefor))
                                {
                                    error=false;
                                }
                                else
                                {
                                    cout<<"Instruccion else sin if previo. ";
                                    error=true;
                                }
                            }
                            else
                                if(SIN.sintaxInitialVar(lineCode))
                                {
                                    string t="", v="";
                                    bool tF=true, vF=false;
                                    for(size_t i(0);i<lineCode.size();++i)
                                    {
                                        if(tF)
                                        {
                                            if(lineCode[i]=='\t'){}
                                            else
                                                if(lineCode[i]!=' ')
                                                {
                                                    t+=lineCode[i];
                                                }
                                                else
                                                {
                                                    tF=false;
                                                    vF=true;
                                                }
                                        }
                                        if(vF)
                                        {
                                            if(lineCode[i]!=';' && lineCode[i]!='=')
                                            {
                                                v+=lineCode[i];
                                            }
                                            else
                                            {
                                                vF=false;
                                            }
                                        }
                                        else
                                            break;

                                    }



                                    error=false;
                                }
                                else
                                    if(SIN.sintaxWhile(lineCode))
                                        error=false;
                                    else
                                        if(SIN.emptyLine(lineCode))
                                            error=false;
                                        else
                                            if(SIN.sintaxBracketOpen(lineCode))
                                            {
                                                if(SIN.sintaxIf(lineBefore)||SIN.sintaxFor(lineBefore)||SIN.sintaxWhile(lineBefore)||SIN.sintaxElse(lineBefore))
                                                {
                                                    error=false;
                                                    ++contLlaves;
                                                }
                                                else
                                                {
                                                    cout<<"Apertura de llaves invalida. ";
                                                    error=true;
                                                }
                                            }
                                            else
                                                if(SIN.sintaxBracketClose(lineCode))
                                                {
                                                    --contLlaves;
                                                    if(contLlaves<0)
                                                    {
                                                        cout<<"Cerradura invalida de llaves. ";
                                                        error=true;
                                                        contLlaves=0;
                                                    }
                                                    else
                                                        error=false;
                                                }
                                                else
                                                    if(SIN.sintaxDo(lineCode))
                                                    {
                                                        error=false;
                                                        ++contDo;
                                                    }
                                                    else
                                                        if(SIN.sintaxWhileDo(lineCode))
                                                        {
                                                            --contDo;
                                                            if(contDo<0)
                                                            {
                                                                cout<<"Instruccion while sin do previo. ";
                                                                error=true;
                                                                contDo=0;
                                                            }
                                                            else
                                                            {
                                                                error=false;
                                                            }
                                                        }
                                                        else
                                                            error=true;

        lineBeBefor=lineBefore;
        lineBefore=lineCode;

        if(error)
        {
            cout<<"Error en la linea "<<cont<<endl;
            noneError=false;
        }
        ++cont;
    }

    if(contLlaves!=0)
        cout<<"Error, se espera '}'"<<endl;
    else
        if(contDo!=0)
            cout<<"Error, la sentencia do esta esperando un while"<<endl;
        else
            if(noneError)
                cout<<"Sintaxis correcta!"<<endl;

    code.close();
    return 0;
}
