#pragma once
#include "database.h"
#include "datalog.h"
#include "Graph.h"

class Interpreter{
    private:
        Database Database1;
        Datalog Datalog1;
    public:
        void dlSet(Datalog theInformation);
        void S2D(vector<Predicate> Schemes);
        void F2D(vector<Predicate> Facts);
        void RQUE(vector<Predicate> Queries);
        void rRules(vector<Rule> Rules, bool dependent);
        Relation EvalutatePredicate(Predicate Predicates);
        void rOpt(vector<Rule>Rules);
        string ToString();
};
