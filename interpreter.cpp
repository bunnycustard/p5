#include "interpreter.h"

void Interpreter::dlSet(Datalog Datalog2){
    Datalog1 = Datalog2;
    S2D(Datalog1.GetSchemes());
    F2D(Datalog1.GetFacts());
    RQUE(Datalog1.GetQueries());
}
void Interpreter::S2D(vector<Predicate> Predicates){
    for(unsigned int i = 0; i < Predicates.size(); i++){
        string Name1 = Predicates.at(i).nGet();
        Scheme theScheme;
        for(unsigned int j = 0; j < Predicates.at(i).GetVec().size(); j++){theScheme.pBack(Predicates.at(i).GetVec().at(j).ToString());}
        Relation Relation1;
        Relation1.nSet(Name1);
        Relation1.sSet(theScheme);
        Database1.rAdd(Name1, Relation1);
    }
    
}
void Interpreter::F2D(vector<Predicate> Facts){
    for(unsigned int j = 0; j < Facts.size(); j++){}
        string Name1;
        Name1 = Facts.at(j).nGet();
        Tuple theTuple;
        for(unsigned int i = 0; i < Facts.at(j).GetVec().size(); i++) {theTuple.push_back(Facts.at(j).GetVec().at(i).ToString());}
        Database1.tAddr(Name1, theTuple);
    }
}
void Interpreter::RQUE(vector<Predicate> Queries){
    for(unsigned int i = 0; i < Queries.size(); i++){
        string Name1 = Queries.at(i).nGet();
        vector<int> iVec;
        vector<string> sVec;
        Relation Relation0 = Database1.dbs.at(Name1);
        for(unsigned int j = 0; j < Queries.at(i).GetVec().size(); j++){
            Parameter CP1 = Queries.at(i).GetVec().at(j);
            if(CP1.IsString() == true){
                string yes = CP1.P1;
                Relation0 = Relation0.select(j,yes);
            }
            else{
                bool duplicate = false;
                for(unsigned int k = 0; k < sVec.size(); k++){ 
                    if (sVec.at(k) == CP1.P1) { 
                        duplicate = true;
                        Relation0 = Relation0.select(j,k);
                    }
                }
                if(duplicate == false){
                    sVec.push_back(CP1.P1);
                    iVec.push_back(j);
                }
            }
        }
        Relation Relation1;
        Relation1 = Relation0.jects(iVec);
        Relation0 = Relation1.declare(sVec);
        cout << Queries.at(i).ToString() << "? ";
        if(Relation0.dTup.size() == 0){cout << "No\n";  }
        else {
            cout << "Yes(" << Relation0.dTup.size() <<")\n";
            Relation0.ToString();
        }
    }
}

string Interpreter::ToString() {return Databse1.ToStirng();}
