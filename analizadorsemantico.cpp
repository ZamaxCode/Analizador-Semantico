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

bool AnalizadorSemantico::checarExistencia(const string v1, const string v2, const string v3)
{
    string wi1="", wi2="", wi3="";
    bool b2=false, b3=false;

    //Para una variable
    regex numReg(NumSintax);
    if(v1[0]=='"')
    {
        wi1="s";
    }
    else
        if(regex_match(v1,numReg))
        {
            wi1="n";
        }
        else
        {
            size_t j;
            for(j=0;j<varArray.size();++j)
            {
                if(v1==varArray.at(j).getVariable())
                {
                    if(varArray.at(j).getTipo()=="string")
                        wi1="s";
                    else
                        wi1="n";
                    break;
                }
            }
            if(j==varArray.size())
            {
                cout<<"La variable \""<<v1<<"\" no existe. ";
                return false;
            }
        }

    //Para dos variables
    if(v2.size()>0)
    {
        if(v2[0]=='"')
        {
            wi2="s";
        }
        else
            if(regex_match(v2,numReg))
            {
                wi2="n";
            }
            else
            {
                size_t j;
                for(j=0;j<varArray.size();++j)
                {
                    if(v2==varArray.at(j).getVariable())
                    {
                        if(varArray.at(j).getTipo()=="string")
                            wi2="s";
                        else
                            wi2="n";
                        break;
                    }
                }
                if(j==varArray.size())
                {
                    cout<<"La variable \""<<v2<<"\" no existe. ";
                    return false;
                }
            }

        b2=true;

        //Para tres variables
        if(v3.size()>0)
        {
            if(v3[0]=='"')
            {
                wi3="s";
            }
            else
                if(regex_match(v3,numReg))
                {
                    wi3="n";
                }
                else
                {
                    size_t j;
                    for(j=0;j<varArray.size();++j)
                    {
                        if(v3==varArray.at(j).getVariable())
                        {
                            if(varArray.at(j).getTipo()=="string")
                                wi3="s";
                            else
                                wi3="n";
                            break;
                        }
                    }
                    if(j==varArray.size())
                    {
                        cout<<"La variable \""<<v3<<"\" no existe. ";
                        return false;
                    }
                }

            b3=true;
        }
    }

    if(!b2 && !b3)
    {
        return true;
    }
    else if(b2 && !b3)
    {
        if(wi1==wi2)
            return true;
        else
        {
            cout<<"\""<<v1<<"\" no es compatible con \""<<v2<<"\". ";
            return false;
        }
    }
    else
    {
        if(wi1==wi2&&wi1==wi3)
            return true;
        else
        {
            cout<<"Los datos son incompatibles";
            return false;
        }
    }

}
