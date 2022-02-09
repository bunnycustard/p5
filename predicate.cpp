#include "predicate.h"

void Predicate::NameSetter(string Name1){Name = Name1;}
void Predicate::PPush(Parameter theParameter){
    paramlist.push_back(theParameter);
    return;
}
vector<Parameter> Predicate::GetVec(){return paramlist;}

string Predicate::ToString(){
    string pString = Name + "(";
    for (unsigned int i = 0; i < paramlist.size(); i++){
        if(i ==0 ){pString = pString + paramlist.at(i).ToString();}
        else{pString = pString + "," + paramlist.at(i).ToString();}
    }
    pString = pString + ")";
    return pString;
}
