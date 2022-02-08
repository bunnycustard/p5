#include "parser.h"

Parser::Parser() {}
Parser::~Parser(){}

bool Parser::DatalogProgram(queue<Token> Tokens){
    Parse(Tokens);
    return failed;
}

string Parser::ToString(){
    if(failed != true){
        string thing;
        cout << Everything.ToString();
        return thing;
    }
    else{
        string stringy;
        return stringy;
    }
}

Datalog Parser::Parse(queue<Token> Tokens){
    tQueue = Tokens;
    vector<Predicate> Schemes;
    ParseCheck(SCHEMES);
    ParseCheck(COLON);
    Schemes.push_back(ParseScheme());
    Schemes = ParseSchemeList(Schemes);
    if (failed == false) {
        Everything.SchemesSetter(Schemes);
    }
    else {
        return Everything;
    }

    if(failed == false) {
        ParseCheck(FACTS);
        ParseCheck(COLON);
        vector<Predicate> parsedFacts; 
        parsedFacts = ParseFactList(parsedFacts);
        if (failed == false) {
            Everything.FactsSetter(parsedFacts);
            Everything.DomainSetter(Domain);
        }
        else {
            return Everything;
    }
    }
    else {
        return Everything;
    }

    if(failed == false) {
        vector<Rule> Rules;
        ParseCheck(RULES);
        ParseCheck(COLON);
        Rules = ParseRuleList(Rules);
        if (failed == false) {
            Everything.RulesSetter(Rules);
        }
        else {
            return Everything;
        }
    }
    else {
        return Everything;
    }
    if (failed == false) {
        vector<Predicate> Queries;
        ParseCheck(QUERIES);
        ParseCheck(COLON);
        Queries.push_back(ParseQuery());
        Queries = ParseQueryList(Queries);
        if ( failed == false) {
            Everything.QueriesSetter(Queries);
        }
        else {
            return Everything;
    }
    }
    else {
        return Everything;
    }
    if (failed == false) {
        if (Token2.GetType() == EOFa) {
            cout << "Success!" << endl;
            return Everything;
        }
        else {
            while (Token2.GetType() != EOFa) {
                Token1 = tQueue.front();
                tQueue.pop();
                Token2 = tQueue.front();
            }
            PrintFail(Token1.linenumber());
            return Everything;
        }
    }
    else {
        return Everything;
    }
}

Predicate Parser::ParseQuery() {
    Predicate Query;
    if (failed == false) {
        Query = ParsePredicate();
        ParseCheck(Q_MARK);
        return Query;
    }
    else {
        return Query;
    }
}

vector<Predicate> Parser::ParseQueryList(vector<Predicate> Queries) {
    if (failed == false) {
        if (Token2.GetType() != ID) {
            return Queries;
        }
        else {
            Queries.push_back(ParseQuery());
            Queries = ParseQueryList(Queries);
            return Queries;
        }
    }
    else {
        return Queries;
    }
}

vector<Rule> Parser::ParseRuleList(vector<Rule> RuleList) {
    if(failed == false) {
        if (Token2.GetType() == QUERIES) {
            return RuleList;
        }
        else {
            RuleList.push_back(ParseRules());
            RuleList = ParseRuleList(RuleList);
            return RuleList;
        }
    }
    else {
        return RuleList;
    }
}

Rule Parser::ParseRules() {
    Rule theRule;
    vector<Predicate> listOfRules;
    Predicate rule;
    if (failed == false) {
        theRule.SetHeadPredicate(ParseHeadPredicate());
        ParseCheck(COLON_DASH);
        rule = ParsePredicate();
        listOfRules.push_back(rule);
        listOfRules = ParsePredicateList(listOfRules);
        ParseCheck(PERIOD);
        theRule.SetRule(listOfRules);
        return theRule;
    }
    else {
        return theRule;
    }
}

vector<Predicate> Parser::ParseFactList(vector<Predicate> Facts) {
    Predicate newFact;
    if (failed == false) {
        if (Token2.GetType() == RULES) {
            return Facts; 
        }
        else {
            newFact = ParseFact();
            Facts.push_back(newFact);
            vector<Parameter> parameters;
            parameters = newFact.ReturnVector();
            for (unsigned int i = 0; i < parameters.size(); i++) {
                Domain.insert(parameters.at(i).ToString());
            }
            Facts = ParseFactList(Facts);
            return Facts;
        }
    }
    else {
        return Facts;
    }
}

Predicate Parser::ParseFact() {
    Predicate Facts;
    if (failed == false) {
        parameters.clear();
        ParseCheck(ID);
        Facts.SetName(Token1.GetValue());
        ParseCheck(LEFT_PAREN);
        ParseCheck(STRING);
        PushOnList(Token1.GetValue());
        Domain.insert(Token1.GetValue());
        ParseStringList();
        ParseCheck(RIGHT_PAREN);
        ParseCheck(PERIOD);
        for (unsigned int i = 0; i < parameters.size(); i++) {
            Facts.PushPredicate(parameters.at(i));
        }
        return Facts;
    }
    else {
        return Facts;
    } 
}

void Parser::ParseStringList(){
    if (failed == false) {
        if (Token2.GetType() == COMMA) {
            ParseCheck(COMMA);
            ParseCheck(STRING);
            PushOnList(Token1.GetValue());
            ParseStringList();
        }
        else {
            return;
        }
    }
    else {
        return;
    }
}

Predicate Parser::ParseScheme() {
    Predicate Schemes;
    if (failed == false) {
        parameters.clear();
        ParseCheck(ID);
        Schemes.SetName(Token1.GetValue());
        ParseCheck(LEFT_PAREN);
        ParseCheck(ID);
        PushOnList(Token1.GetValue());
        ParseIDList();
        ParseCheck(RIGHT_PAREN);
        for (unsigned int i = 0; i < parameters.size(); i++) {
            Schemes.PushPredicate(parameters.at(i));
        }
        return Schemes;
    }
    else {
        return Schemes;
    }
}

vector<Predicate> Parser::ParseSchemeList(vector<Predicate> Schemes) {
    Predicate newScheme; 
    if (failed == false) {
        if (Token2.GetType() == FACTS) {
            return Schemes;
        }
        else {
            newScheme = ParseScheme();
            Schemes.push_back(newScheme);
            Schemes = ParseSchemeList(Schemes);
            return Schemes;
        }
    }
    else {
        return Schemes;
    }
}

void Parser::ParseIDList() {
    if (failed == false) {
        if (Token2.GetType() == COMMA) {
            ParseCheck(COMMA);
            ParseCheck(ID);
            PushOnList(Token1.GetValue());
            ParseIDList();
        }
        else {
            return;
        }
    }
    else {
        return;
    }
}

bool Parser::CheckNext(TokenType type) {
    if (failed == false) {
        if (Token2.GetType() == type) {
            return true;
        }
        else {
            PrintFail(Token2.linenumber());
            return false;
        }
    }
    else {
        return false;
    }
}

bool Parser::ParseCheck(TokenType type) {
    if (failed == false) {
        if (Token2.GetType() != EOFa) {
            Token1 = tQueue.front();
            tQueue.pop();
            Token2 = tQueue.front();
            if (Token1.GetType() == type) {
                return true; 
            }
            else {
                PrintFail(Token1.linenumber());
                return false;
            }
        }
        else {
            Token1 = tQueue.front();
            return true;
        }
    }
    else {
        if (Token2.GetType() != EOFa) {
            Token1 = tQueue.front();
            tQueue.pop();
            Token2 = tQueue.front();
        }
        else {
            Token1 = tQueue.front();
        }
        return false;
    }
}

void Parser::PrintFail(int i) {
    cout << "Failure!" << "\n  (" << Token1.toString2() << ",\"" <<Token1.GetValue() <<"\"," << i << ")" << endl;
    failed = true;
    return;
}

Predicate Parser::ParseHeadPredicate() {
    Predicate headPredicate;
    if (failed == false) {
        parameters.clear();
        ParseCheck(ID);
        headPredicate.SetName(Token1.GetValue());
        ParseCheck(LEFT_PAREN);
        ParseCheck(ID);
        PushOnList(Token1.GetValue());
        ParseIDList();
        ParseCheck(RIGHT_PAREN);
        for (unsigned int i = 0; i < parameters.size(); i++) {
            headPredicate.PushPredicate(parameters.at(i));
        }
        return headPredicate;
    }
    else {
        return headPredicate;
    }
}

vector<Predicate> Parser::ParsePredicateList(vector<Predicate> list) {
    if (failed == false) {
        if (Token2.GetType() == COMMA) {
            ParseCheck(COMMA);
            list.push_back(ParsePredicate());
            list = ParsePredicateList(list);
            return list;
        }
        else {
            return list;
        }
    }
    else {
        return list;
    }
}

Predicate Parser::ParsePredicate(){
    Predicate Predicates;
    Parameter newParam;
    if (failed == false) {
        parameters.clear();
        ParseCheck(ID);
        Predicates.SetName(Token1.GetValue());
        ParseCheck(LEFT_PAREN);
        newParam = ParseParameter();
        PushOnList(newParam.ToString());
        ParseParameterList();
        ParseCheck(RIGHT_PAREN);
        for (unsigned int i = 0; i < parameters.size(); i++) {
            Predicates.PushPredicate(parameters.at(i));
        }
        return Predicates;
    }
    else {
        return Predicates;
    }
}

void Parser::PushOnList(string token) {
    Parameter newParam;
    if (Token1.GetValue() != "") {
        newParam.SetParam(token);
        parameters.push_back(newParam);
    }
    else {
    }
    return;
}

Parameter Parser::ParseParameter() {
    Parameter newParam;
    if (failed == false) {
        Token toSend = Token2;
        if (Token2.GetType() == STRING) {
            ParseCheck(STRING);
            newParam.SetParam(Token1.GetValue());
            return newParam;
        }   
        else if (Token2.GetType() == ID) {
            ParseCheck(ID);
            newParam.SetParam(Token1.GetValue());
            return newParam;
        }
        else if (Token2.GetType() == LEFT_PAREN) {
            string stringy;
            stringy = ParseExpression();
            stringy = "(" + stringy + ")";
            newParam.SetParam(stringy);
            return newParam;
        }
        else {
            Token1 = Token2;
            CheckNext(ERROR);
            return newParam;
        }
    }
    else {
        return newParam;
    }
}

void Parser::ParseParameterList() {
    if (failed == false) {
        if (Token2.GetType() == RIGHT_PAREN) {
            return;
        }
        else {
            Parameter newParam;
            ParseCheck(COMMA);
            newParam = ParseParameter();
            PushOnList(newParam.ToString());
            ParseParameterList();
            return;
        }
    }
    else {
        return;
    }
}

string Parser::ParseExpression() {
    if (failed == false) {
        Expression theExpression;
        Parameter newParam;

        ParseCheck(LEFT_PAREN);
        newParam = ParseParameter();
        theExpression.SetRight(newParam);
        newParam.SetParam(ParseOperator().GetValue());
        theExpression.SetOperator(newParam);
        newParam = ParseParameter();
        theExpression.SetLeft(newParam);
        ParseCheck(RIGHT_PAREN);

        return theExpression.GetExpression();
    }
    else {
        string list;
        return list;
    }
}

Token Parser::ParseOperator() {
    if (failed == false) {
        if (Token2.GetType() == ADD) {
            ParseCheck(ADD);
        }
        else if (Token2.GetType() == MULTIPLY) {
            ParseCheck(MULTIPLY);
        }
        else {
            ParseCheck(MULTIPLY);
        }
        return Token1;
    }
    else {
        return Token1;
    }
}
