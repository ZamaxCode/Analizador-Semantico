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
        if(SIN.sintaxAssign(lineCode))//ASIGNACION
        {
            string v1="", v2="", v3="";
            bool t=true, b1=true, b2=false, b3=false;
            for(size_t j(0);j<lineCode.size();++j)
            {
                if(t)
                {
                    if(lineCode[j]=='\t'){}
                    else
                    {
                        t=false;
                        --j;
                    }
                }
                else
                {
                    if(b1)
                    {
                        if(lineCode[j]!='=')
                            v1+=lineCode[j];
                        else
                        {
                            b1=false;
                            b2=true;
                        }
                    }
                    else
                        if(b2)
                        {
                            if(lineCode[j]!='+' && lineCode[j]!='-' && lineCode[j]!='*' && lineCode[j]!='/' && lineCode[j]!=';')
                                v2+=lineCode[j];
                            else
                            {
                                b2=false;
                                if(lineCode[j]!=';')
                                    b3=true;
                            }
                        }
                        else
                            if(b3)
                            {
                                if(lineCode[j]!=';')
                                    v3+=lineCode[j];
                                else
                                    b3=false;

                            }
                }
            }

            if(SEM.checarExistencia(v1,v2,v3))
                error=false;
            else
                error=true;
        }
        else
            if(SIN.sintaxCin(lineCode))//CIN
            {
                string v="";
                bool t=true;
                for(size_t j(0);j<lineCode.size();++j)
                {
                    if(t)
                    {
                        if(lineCode[j]=='\t'){}
                        else
                        {
                            j+=4;
                            t=false;
                        }
                    }
                    else
                    {
                        if(lineCode[j]==';')
                            break;
                        v+=lineCode[j];
                    }
                }
                if(SEM.checarExistencia(v,"",""))
                    error=false;
                else
                    error=true;
            }
            else
                if(SIN.sintaxCout(lineCode))//COUT
                {
                    string v="";
                    bool t=true, brk=false;
                    for(size_t j(0);j<lineCode.size();++j)
                    {
                        if(t)
                        {
                            if(lineCode[j]=='\t'){}
                            else
                            {
                                j+=5;
                                t=false;
                            }
                        }
                        else
                        {
                            if(lineCode[j]!='<'&&lineCode[j]!=';')
                            {
                                v+=lineCode[j];
                            }
                            else
                            {
                                if(lineCode[j]=='<')
                                {
                                    ++j;
                                    if(!SEM.checarExistencia(v,"",""))
                                    {
                                        error=true;
                                        brk=true;
                                    }
                                    v.clear();
                                }
                                else
                                {
                                    if(lineCode[j]==';')
                                    {
                                        if(!SEM.checarExistencia(v,"",""))
                                            error=true;
                                        else
                                            error=false;
                                        brk=true;
                                    }
                                }
                            }
                        }

                        if(brk)
                            break;
                    }
                }
                else
                    if(SIN.sintaxFor(lineCode))//FOR
                    {
                        string v1="", v2="", v3="", v4="", v5="";
                        bool t=true, b1=true, b2=false, b3=false, b4=false, b5=false;
                        size_t j;
                        for(j=0;j<lineCode.size();++j)
                        {
                            if(t)
                            {
                                if(lineCode[j]=='\t'){}
                                else
                                {
                                    j+=3;
                                    t=false;
                                }
                            }
                            else
                            {
                                if(b1)
                                {
                                    if(lineCode[j]!='=')
                                        v1+=lineCode[j];
                                    else
                                    {
                                        b1=false;
                                        b2=true;
                                    }
                                }
                                else
                                    if(b2)
                                    {
                                        if(lineCode[j]!=';')
                                            v2+=lineCode[j];
                                        else
                                        {
                                            b2=false;
                                            b3=true;
                                            if(!SEM.checarExistencia(v1,v2,""))
                                            {
                                                error=true;
                                                break;
                                            }

                                        }
                                    }
                                    else
                                        if(b3)
                                        {
                                            if(lineCode[j]!='<' && lineCode[j]!='>' && lineCode[j]!='=' && lineCode[j]!='!')
                                                v3+=lineCode[j];
                                            else
                                            {
                                                if(lineCode[j+1]=='=')
                                                    ++j;
                                                b3=false;
                                                b4=true;
                                            }
                                        }
                                        else
                                            if(b4)
                                            {
                                                if(lineCode[j]!=';')
                                                    v4+=lineCode[j];
                                                else
                                                {
                                                    b4=false;
                                                    b5=true;
                                                    if(!SEM.checarExistencia(v3,v4,""))
                                                    {
                                                        error=true;
                                                        break;
                                                    }

                                                }
                                            }
                                            else
                                                if(b5)
                                                {
                                                    if(lineCode[j]!='+' && lineCode[j]!='-')
                                                        v5+=lineCode[j];
                                                    else
                                                    {
                                                        b5=false;
                                                        if(!SEM.checarExistencia(v5,"",""))
                                                        {
                                                            error=true;
                                                            break;
                                                        }

                                                    }
                                                }
                            }
                        }
                        if(j==lineCode.size())
                            error=false;
                    }
                    else
                        if(SIN.sintaxIf(lineCode))//IF
                        {
                            string v1="", v2="";
                            bool t=true, b1=true, b2=false;
                            for(size_t j(0);j<lineCode.size();++j)
                            {
                                if(t)
                                {
                                    if(lineCode[j]=='\t'){}
                                    else
                                    {
                                        j+=2;
                                        t=false;
                                    }
                                }
                                else
                                {
                                    if(b1)
                                    {
                                        if(lineCode[j]!='<' && lineCode[j]!='>' && lineCode[j]!='=' && lineCode[j]!='!')
                                            v1+=lineCode[j];
                                        else
                                        {
                                            if(lineCode[j+1]=='=')
                                                ++j;
                                            b1=false;
                                            b2=true;
                                        }
                                    }
                                    else
                                        if(b2)
                                        {
                                            if(lineCode[j]!=')')
                                                v2+=lineCode[j];
                                            else
                                            {
                                                b2=false;
                                            }
                                        }
                                }
                            }
                            if(SEM.checarExistencia(v1,v2,""))
                                error=false;
                            else
                                error=true;
                        }
                        else
                            if(SIN.sintaxElse(lineCode))//ELSE
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
                                if(SIN.sintaxInitialVar(lineCode))//INICIALIZACION
                                {
                                    if(SEM.declararVariable(lineCode))
                                    {
                                        error=false;
                                    }
                                    else
                                    {
                                        error=true;
                                    }
                                }
                                else
                                    if(SIN.sintaxWhile(lineCode))//WHILE
                                    {
                                        string v1="", v2="";
                                        bool t=true, b1=true, b2=false;
                                        for(size_t j(0);j<lineCode.size();++j)
                                        {
                                            if(t)
                                            {
                                                if(lineCode[j]=='\t'){}
                                                else
                                                {
                                                    j+=5;
                                                    t=false;
                                                }
                                            }
                                            else
                                            {
                                                if(b1)
                                                {
                                                    if(lineCode[j]!='<' && lineCode[j]!='>' && lineCode[j]!='=' && lineCode[j]!='!')
                                                        v1+=lineCode[j];
                                                    else
                                                    {
                                                        if(lineCode[j+1]=='=')
                                                            ++j;
                                                        b1=false;
                                                        b2=true;
                                                    }
                                                }
                                                else
                                                    if(b2)
                                                    {
                                                        if(lineCode[j]!=')')
                                                            v2+=lineCode[j];
                                                        else
                                                        {
                                                            b2=false;
                                                        }
                                                    }
                                            }
                                        }
                                        if(SEM.checarExistencia(v1,v2,""))
                                            error=false;
                                        else
                                            error=true;
                                    }
                                    else
                                        if(SIN.emptyLine(lineCode))//EMPTY LINE
                                            error=false;
                                        else
                                            if(SIN.sintaxBracketOpen(lineCode))//{
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
                                                if(SIN.sintaxBracketClose(lineCode))//}
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
                                                    if(SIN.sintaxDo(lineCode))//DO
                                                    {
                                                        error=false;
                                                        ++contDo;
                                                    }
                                                    else
                                                        if(SIN.sintaxWhileDo(lineCode))//WHILE (DO)
                                                        {

                                                            string v1="", v2="";
                                                            bool t=true, b1=true, b2=false, good=false;
                                                            for(size_t j(0);j<lineCode.size();++j)
                                                            {
                                                                if(t)
                                                                {
                                                                    if(lineCode[j]=='\t'){}
                                                                    else
                                                                    {
                                                                        j+=6;
                                                                        t=false;
                                                                    }
                                                                }
                                                                else
                                                                {
                                                                    if(b1)
                                                                    {
                                                                        if(lineCode[j]!='<' && lineCode[j]!='>' && lineCode[j]!='=' && lineCode[j]!='!')
                                                                            v1+=lineCode[j];
                                                                        else
                                                                        {
                                                                            if(lineCode[j+1]=='=')
                                                                                ++j;
                                                                            b1=false;
                                                                            b2=true;
                                                                        }
                                                                    }
                                                                    else
                                                                        if(b2)
                                                                        {
                                                                            if(lineCode[j]!=')')
                                                                                v2+=lineCode[j];
                                                                            else
                                                                            {
                                                                                b2=false;
                                                                            }
                                                                        }
                                                                }
                                                            }
                                                            if(SEM.checarExistencia(v1,v2,""))
                                                            {
                                                                error=false;
                                                                good=true;
                                                            }
                                                            else
                                                                error=true;

                                                            --contDo;
                                                            if(contDo<0)
                                                            {
                                                                cout<<"Instruccion while sin do previo. ";
                                                                error=true;
                                                                contDo=0;
                                                            }
                                                            else
                                                            {
                                                                if(good)
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

    SEM.buscarNoUsadas();

    code.close();
    return 0;
}
