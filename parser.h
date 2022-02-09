#pragma once

#include <queue>

#include "token.h"
#include "datalog.h"
#include "expression.h"

class Parser{
		protected:
        Token Token1;
        Token Token2;
        queue<Token> tQueue;
        vector<Parameter> parameters;
        bool failed = false;
        set<string> Domain;
        Datalog All;

        void WhenFailed(int i = 0);
        bool Continue(TokenType type);

        Datalog Parse(queue<Token> Tokens);
        bool pCheck(TokenType type);
        Predicate pScheme();
        vector<Predicate> pSchemeList(vector<Predicate> Schemes);
        void pIDList();
        vector<Predicate> pFactList(vector<Predicate> Facts);
        Predicate pFact();
        void pStringList();
        vector<Rule> pRuleList(vector<Rule> Rules);
        Rule pRules();
        Predicate pQuery();
        vector<Predicate> pQueryList(vector<Predicate> Queries);

        Predicate pHeadPredicate();
        Predicate pPredicate();
        vector<Predicate> pPredicateList(vector<Predicate>);

        Parameter pParameter();
        void pParameters();
        string pExpression();
        Token pOperator();

        void Pusher(string token);
				
    public:
        Parser();
        ~Parser();

        string ToString();
        bool Logger(queue<Token> Tokens);
};
