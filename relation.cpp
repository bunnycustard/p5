#include "relation.h"

string Relation::ToString(){
    string opstr;
        for(auto i : dTup){
            if(Scheme1.Size() != 0) {cout << "  ";}
            for(unsigned int j = 0; j < Scheme1.Size(); j++){
                cout << Scheme1.At(j) + "=" + i.at(j);
                if(j < Scheme1.Size()-1) {cout << ", ";}
            }
            if(Scheme1.Size() != 0){cout << "\n";}
        }
        return opstr;
}

Relation Relation::select(int ind, string value){
    Relation Relation1, Relation2;
    Relation1.nSet(name);
    Relation1.sSet(Scheme1);
    Relation2.nSet(name);
    Relation2.sSet(Scheme1);
    Relation2.nSet(name);
    Relation2.sSet(Scheme1);
    for(auto i: dTup){Relation2.tAdd(i);}
    for(auto i: dTup){if (i.at(ind) == value) {Relation1.tAdd(i);}}
    return Relation1;
}

Relation Relation::select(int indOne, int indTwo){
    Relation Relation1, Relation2;
    Relation1.nSet(name);
    Relation1.sSet(Scheme1);
    Relation2.nSet(name);
    Relation2.sSet(Scheme1);
    for(auto i: dTup){Relation2.tAdd(i);}
    for(auto i: dTup){if (i.at(indOne) == i.at(indTwo)) {Relation1.tAdd(i);}}
    return Relation1;
}

Relation Relation::jects(vector<int> indicies){
    Relation Relation1;
    Relation1.nSet(name);
    for(auto i: dTup){
        Tuple PHT;
        for(unsigned j = 0; j < indicies.size(); j++) {PHT.push_back(i.at(indicies.at(j)));}
        Relation1.tAdd(PHT);
    }
    Scheme PHSch;
    for(unsigned int i = 0; i < indicies.size(); i++ ){PHSch.pBack(Scheme1.at(indicies.at(i)));}
    Relation1.sSet(PHSch);
    return Relation1;
}

Relation Relation::declare(vector<string> names){
    Scheme PHS;
    PHS.sGet(names);
    Relation Relation1;
    Relation1.nSet(name);
    Relation1.sSet(PHS);
    for(auto i : dTup){Relation1.tAdd(i);}
    return Relation1;
}

void Relation::tAdd(Tuple tuples){dTup.insert(tuples);}
void Relation::sSet(Scheme dSch){Scheme1 = dSch;} 
void Relation::nSet(string dName){name = dName;}
