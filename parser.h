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
        Predicate ParseScheme();
        vector<Predicate> ParseSchemeList(vector<Predicate> Schemes);
        void ParseIDList();
        vector<Predicate> ParseFactList(vector<Predicate> Facts);
        Predicate ParseFact();
        void ParseStringList();
        vector<Rule> ParseRuleList(vector<Rule> Rules);
        Rule ParseRules();
        Predicate ParseQuery();
        vector<Predicate> ParseQueryList(vector<Predicate> Queries);

        Predicate ParseHeadPredicate();
        Predicate ParsePredicate();
        vector<Predicate> ParsePredicateList(vector<Predicate>);

        Parameter ParseParameter();
        void ParseParameterList();
        string ParseExpression();
        Token ParseOperator();

        void PushOnList(string token);
				
    public:
        Parser();
        ~Parser();

        string ToString();
        bool Logger(queue<Token> Tokens);
};
