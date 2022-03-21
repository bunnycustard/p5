#pragma once
#include "predicate.h"

class Rule{
    public:
        void HPSetter(Predicate head);
        void RuleSetter(vector<Predicate> Toke);
        Predicate Head;
        vector<Predicate> RuleList;
				
        string ToString();
};
