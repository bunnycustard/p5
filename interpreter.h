#pragma once
#include "database.h"
#include "datalog.h"

class Interpreter{
    private:
        Database Database1;
        Datalog Datalog1;
    public:
        void dlSet(Datalog theInformation);
        void S2D(vector<Predicate> Schemes);
        void F2D(vector<Predicate> Facts);
        void RQUE(vector<Predicate> Queries);
        string ToString();
};
