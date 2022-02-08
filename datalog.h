#pragma once
#include <set>
#include "rules.h"

enum PredicateType{Facts,Queries,Schemes};

class Datalog{
    private:
        vector<Predicate> Facts;
        vector<Predicate> Queries;
        vector<Rule> Rules;
        vector<Predicate> Schemes;
        set<string> Domain;
				
    public:
        void FactsSetter(vector<Predicate> Fact);
        void QueriesSetter(vector<Predicate> Query);
        void RulesSetter(vector<Rule> Rule);
        void SchemesSetter(vector<Predicate> Scheme);
        void DomainSetter(set<string> Set);
        vector<Predicate> GetFacts();
        vector<Predicate> GetQueries();
        vector<Rule> GetRules();
        vector<Predicate> GetSchemes();
        string ToString();
};
