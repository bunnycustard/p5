#include "interpreter.h"

void Interpreter::dlSet(Datalog Datalog2){
    Datalog1 = Datalog2;
    S2D(Datalog1.GetSchemes());
    F2D(Datalog1.GetFacts());
	  rOpt(Datalog1.GetRules());
    cout << endl << "Query Evaluation" << endl;
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
    for(unsigned int j = 0; j < Facts.size(); j++){
        string Name1;
        Name1 = Facts.at(j).nGet();
        Tuple theTuple;
        for(unsigned int i = 0; i < Facts.at(j).GetVec().size(); i++) {theTuple.push_back(Facts.at(j).GetVec().at(i).ToString());}
        Database1.tAddr(Name1, theTuple);
    }
    return;
}
void Interpreter::RQUE(vector<Predicate> Queries){
    for(unsigned int i = 0; i < Queries.size(); i++){
        Relation TempRelation = EvalutatePredicate(Queries.at(i));
        cout << Queries.at(i).ToString() << "? ";
        if(TempRelation.dTup.size() == 0){cout << "No\n";  }
        else{
            cout << "Yes(" << TempRelation.dTup.size() <<")\n";
            TempRelation.ToString();
        }
    }
    return;
}

void Interpreter::rRules(vector<Rule> Rules, bool what){
    bool Tuples2 = true;
    int rulesPass =0;
    while(Tuples2){
        Tuples2 = false;
        vector <bool> cont;
        rulesPass++;
        for(unsigned int i = 0; i < Rules.size(); i ++){
            cout << Rules.at(i).ToString()<< endl;
            vector <Relation> Relations1; 
            for(unsigned int j = 0; j < Rules.at(i).RuleList.size(); j ++ ){
                Relation Relation0 = EvalutatePredicate(Rules.at(i).RuleList.at(j));
                Relations1.push_back(Relation0);
            }
            Relation Relation0;
            if(Relations1.size() > 1){
                Relation0 = Relations1.at(0);
                for(unsigned int j = 0; j < Relations1.size()-1; j++ ){Relation0 = Relation0.Join(Relations1.at(j+1));}
            }
            else{Relation0 = Relations1.at(0);}
            vector <int> Indicies;
            for(unsigned int j = 0; j < Rules.at(i).Head.paramlist.size(); j++){
                for(unsigned int k = 0; k < Relation0.  Scheme1.Size(); k++){
                    if(Rules.at(i).Head.paramlist.at(j).P1 == Relation0.  Scheme1.At(k)){Indicies.push_back(k);}
                }
            }
            Relation0 = Relation0.jects(Indicies);
            Relation0.name = Rules.at(i).Head.Name;
            if (Database1.dbs.at(Relation0.name).  Scheme1.values.size() == Relation0.  Scheme1.values.size()) {
                Relation0.  Scheme1 = Database1.dbs.at(Relation0.name).  Scheme1;
            }
            else {}
            cont.push_back(Database1.dbs.at(Relation0.name).Unite(Relation0));
        }
        for(unsigned int a = 0; a <cont.size(); a++){
            if(cont.at(a)){Tuples2 = true;} 
        }
				if(!what){Tuples2 = false;}
    }
    cout << rulesPass << " passes: ";
    return;
}

Relation Interpreter::EvalutatePredicate(Predicate Queries){
        string Name1 = Queries.nGet();
        vector<int> theInts;
        vector<string> theStrings;
        Relation Relation0 = Database1.dbs.at(Name1);
        for(unsigned int j = 0; j < Queries.GetVec().size(); j++){ 
            Parameter CP1 = Queries.GetVec().at(j);
            if(CP1.IsString() == true){
                string yes = CP1.P1;
                Relation0 = Relation0.select(j,yes);
            }
            else{ 
                bool duplicate = false;
                for (unsigned int k = 0; k < theStrings.size(); k++) {    
                    if (theStrings.at(k) == CP1.P1) { 
                        duplicate = true;
                        Relation0 = Relation0.select(j,k);
                    }
                }
                if(duplicate == false){
                    theStrings.push_back(CP1.P1);
                    theInts.push_back(j);
                }
            }
        }
        Relation0 = Relation0.jects(theInts);
        Relation0 = Relation0.declare(theStrings);
        return Relation0;
}

void Interpreter::rOpt(vector<Rule>Rules) {
    Graph Forward, Backwards;
    vector<string> test;
    int open = (int) Rules.size();
    for (int i = 0; i < open; i ++) {
        Node Node2;
        Node2.id = i;
        Node2.sustainable = false;
        Forward.nList.insert({i, Node2});
        Backwards.nList.insert({i, Node2});
    }
    for ( int i = 0; i < open; i++) {
        bool addpunch = false;
        int open1 = (int) Rules.at(i).RuleList.size();
        for (int j = 0; j < open1; j++) {
            for (int k = 0; k < open; k++) {
                if (Rules.at(i).RuleList.at(j).Name == Rules.at(k).Head.Name) {
                    bool sustain = false;
                    if (i==k){sustain = true;}
                    if(Forward.nList[i].sustainable) {sustain = true;}
                    Forward.addEdge(i,k, sustain);
                    Backwards.addEdge(k,i, sustain);
                    addpunch = true;
                }
            }
        }
        if (!addpunch){}
    }
    Forward.ToString();
    Backwards.dfsF();
    Forward.topocate = Backwards.topocate;
    Forward.dfsFF();
    cout <<endl<< "Rule Evaluation" << endl;
    for(unsigned int i = 0; i < Forward.scc.size(); i ++){
        vector<Rule> Spec;
        string hey;
        unsigned int k = 0;
        bool what;
        for(auto j: Forward.scc.at(i)){
            Spec.push_back(Rules.at(j));
            string x = to_string(j);
            hey = hey + "R" + x;
            if (k != Forward.scc.at(i).size() - 1) {hey = hey + ",";}
            k++;
            what = Forward.nList[j].sustainable;
        }
        
        if(Forward.scc.at(i).size() != 1){what = true;}
        cout << "SCC: " << hey << endl; 
        rRules(Spec, what);
        cout << hey << endl;
    }
    return; 
}

string Interpreter::ToString() {return Database1.ToStirng();}
