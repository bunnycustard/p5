#pragma once

#include "predicate.h"

class Rule{
    private:
        Predicate Head;
        vector<Predicate> RuleList;
    public:
        void HeadPredicateSetter(Predicate head);
        void RuleSetter(vector<Predicate> T);
        string ToString();
};
