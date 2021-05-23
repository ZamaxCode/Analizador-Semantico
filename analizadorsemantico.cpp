#include "analizadorsemantico.h"

AnalizadorSemantico::AnalizadorSemantico()
{

}

bool AnalizadorSemantico::declararVariable(const string lineCode)
{
    string t="", v="", a="";
    bool tF=true, vF=false, aF=false;
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
        else
            if(vF)
            {
                if(lineCode[i]!=';' && lineCode[i]!='=')
                {
                    v+=lineCode[i];
                }
                else
                {
                    if(lineCode[i]=='=')
                        aF=true;
                    vF=false;
                }
            }
            else
                if(aF)
                {
                    if(lineCode[i]!=';')
                    {
                        a+=lineCode[i];
                    }
                    else
                    {
                        aF=false;
                    }
                }
                else
                    break;
    }

    if(a.size()>0)
    {
        regex varReg(VarSintax);
        regex numReg(NumSintax);
        if(a[0]=='"')
        {
            if(t!="string")
            {
                cout<<"La variable \""<<v<<"\" no puede recibir ese valor. ";
                return false;
            }
        }
        else
            if(regex_match(a,varReg))
            {
                size_t j;
                for(j=0;j<varArray.size();++j)
                {
                    if(a==varArray.at(j).getVariable())
                    {
                        if( (varArray.at(j).getTipo()=="string" && (t=="int" || t=="float)")) || (t=="string" && (varArray.at(j).getTipo()=="int" || varArray.at(j).getTipo()=="float)")) )
                        {
                            cout<<"La variable \""<<v<<"\" no es compatible con \""<<a<<"\". ";
                            return false;
                        }
                        break;
                    }
                }
                if(j==varArray.size())
                {
                    cout<<"La variable \""<<a<<"\" no existe. ";
                    return false;
                }
            }
            else
                if(regex_match(a,numReg) && t=="string")
                {
                    cout<<"La variable \""<<v<<"\" no puede recibir ese valor. ";
                    return false;
                }
    }

    for(size_t i(0);i<varArray.size();++i)
    {
        if(v==varArray.at(i).getVariable())
        {
            cout<<"La variable \""<<v<<"\" ya ha sido declarada previamente. ";
            return false;
        }
    }
    Variables newVar;
    newVar.setVariable(v);
    newVar.setTipo(t);
    varArray.push_back(newVar);
    return true;
}
