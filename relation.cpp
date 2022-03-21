#include "relation.h"

Relation Relation::Join(Relation relationToJoin){
    Relation NewRelation;
    vector <int> relationInts, toAddInts;
    NewRelation.Scheme1=Scheme1;
   
    for(unsigned int i = 0; i < relationToJoin.Scheme1.Size(); i++){
        bool isACopy = false;
        for(unsigned int j = 0; j < Scheme1.Size(); j++){
            if (!isACopy) {
                if(Scheme1.At(j) != relationToJoin.Scheme1.At(i)){isACopy = false;}
                else{isACopy = true;}
            }

        }
        if(!isACopy){
            NewRelation.Scheme1.pBack(relationToJoin.Scheme1.At(i));
            toAddInts.push_back(i);
        }
    }
    for(auto i: dTup){
        for(auto j: relationToJoin.dTup){
            if (isJoinable(i, j,Scheme1, relationToJoin.Scheme1)){
                Tuple newTuple = i;
                for(unsigned int k = 0; k < toAddInts.size(); k++){newTuple.push_back(j.at(toAddInts.at(k)));}
                NewRelation.tAdd(newTuple);
            }
        }
    }
    return NewRelation;
} 

bool Relation::isJoinable(Tuple Tuple1, Tuple Tuple2Add, Scheme Scheme1, Scheme Scheme2Add){
    for(unsigned int i = 0; i < Scheme1.Size(); i++){
        for(unsigned int j = 0; j < Scheme2Add.Size(); j++){
            if(Scheme1.At(i) == Scheme2Add.At(j)){
                if(Tuple1.at(i)!= Tuple2Add.at(j)){return false;}
            }
        }
    }
    return true;
}

bool Relation::Unite(Relation toUnite){
    bool returnval = false;
    for (auto i: toUnite.dTup) {
        if(dTup.insert(i).second) {
            returnval = true;
            if (Scheme1.Size() != 0) {cout << "  ";}
            for (unsigned int j = 0; j < Scheme1.Size(); j++) {
                cout << Scheme1.At(j) + "=" + i.at(j);
                if (j < Scheme1.Size()-1) {cout << ", ";}
            }
            if(Scheme1.Size() != 0) {cout << "\n";}
        }
    }
    return returnval;
}

void Relation::ToString(){
        for(auto i : dTup){
            if(Scheme1.Size() != 0) {cout << "  ";}
            for(unsigned int j = 0; j < Scheme1.Size(); j++){
                cout << Scheme1.At(j) + "=" + i.at(j);
                if(j < Scheme1.Size()-1) {cout << ", ";}
            }
            if(Scheme1.Size() != 0){cout << "\n";}
        }
	return;
}

Relation Relation::select(int ind, string value){
    Relation Relation1;
    Relation1.nSet(name);
    Relation1.sSet(Scheme1);
    for(auto i: dTup){if (i.at(ind) == value) {Relation1.tAdd(i);}}
    return Relation1;
}

Relation Relation::select(int indOne, int indTwo){
    Relation Relation1, Relation2;
    Relation1.nSet(name);
    Relation1.sSet(Scheme1);
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
    for(unsigned int i = 0; i < indicies.size(); i++ ){PHSch.pBack(Scheme1.At(indicies.at(i)));}
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
