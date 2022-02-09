#pragma once
#include "predicate.h"

class Rule{
    private:
        Predicate Head;
        vector<Predicate> RuleList;
    public:
        void HPSetter(Predicate head);
        void RuleSetter(vector<Predicate> Toke);
				
        string ToString();
};
