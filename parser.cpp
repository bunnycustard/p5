#include "parser.h"

Parser::Parser() {}
Parser::~Parser(){}

bool Parser::Logger(queue<Token> Tokens){
    Parse(Tokens);
    return failed;
}

string Parser::ToString(){
    if(failed != true){
        string thing;
        cout << All.ToString();
        return thing;
    }
    else{
        string tempstring;
        return tempstring;
    }
}

Datalog Parser::Parse(queue<Token> Tokens){
    tQueue = Tokens;
    vector<Predicate> Schemes;
    pCheck(SCHEMES);
    pCheck(COLON);
    Schemes.push_back(ParseScheme());
    Schemes = ParseSchemeList(Schemes);
    if (failed == false) {
        All.SchemesSetter(Schemes);
    }
    else {
        return All;
    }

    if(failed == false) {
        pCheck(FACTS);
        pCheck(COLON);
        vector<Predicate> parsedFacts; 
        parsedFacts = ParseFactList(parsedFacts);
        if (failed == false) {
            All.FactsSetter(parsedFacts);
            All.DomainSetter(Domain);
        }
        else {
            return All;
    }
    }
    else {
        return All;
    }

    if(failed == false) {
        vector<Rule> Rules;
        pCheck(RULES);
        pCheck(COLON);
        Rules = ParseRuleList(Rules);
        if (failed == false) {
            All.RulesSetter(Rules);
        }
        else {
            return All;
        }
    }
    else {
        return All;
    }
    if (failed == false) {
        vector<Predicate> Queries;
        pCheck(QUERIES);
        pCheck(COLON);
        Queries.push_back(ParseQuery());
        Queries = ParseQueryList(Queries);
        if ( failed == false) {
            All.QueriesSetter(Queries);
        }
        else {
            return All;
    }
    }
    else {
        return All;
    }
    if (failed == false) {
        if (Token2.GetType() == EOFa) {
            cout << "Success!" << endl;
            return All;
        }
        else {
            while (Token2.GetType() != EOFa) {
                Token1 = tQueue.front();
                tQueue.pop();
                Token2 = tQueue.front();
            }
            WhenFailed(Token1.linenumber());
            return All;
        }
    }
    else {
        return All;
    }
}

Predicate Parser::ParseQuery() {
    Predicate Query;
    if (failed == false) {
        Query = ParsePredicate();
        pCheck(Q_MARK);
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
        pCheck(COLON_DASH);
        rule = ParsePredicate();
        listOfRules.push_back(rule);
        listOfRules = ParsePredicateList(listOfRules);
        pCheck(PERIOD);
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
        pCheck(ID);
        Facts.SetName(Token1.GetValue());
        pCheck(LEFT_PAREN);
        pCheck(STRING);
        PushOnList(Token1.GetValue());
        Domain.insert(Token1.GetValue());
        ParseStringList();
        pCheck(RIGHT_PAREN);
        pCheck(PERIOD);
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
            pCheck(COMMA);
            pCheck(STRING);
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
        pCheck(ID);
        Schemes.SetName(Token1.GetValue());
        pCheck(LEFT_PAREN);
        pCheck(ID);
        PushOnList(Token1.GetValue());
        ParseIDList();
        pCheck(RIGHT_PAREN);
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
            pCheck(COMMA);
            pCheck(ID);
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

bool Parser::Continue(TokenType type) {
    if (failed == false) {
        if (Token2.GetType() == type) {
            return true;
        }
        else {
            WhenFailed(Token2.linenumber());
            return false;
        }
    }
    else {
        return false;
    }
}

bool Parser::pCheck(TokenType type) {
    if (failed == false) {
        if (Token2.GetType() != EOFa) {
            Token1 = tQueue.front();
            tQueue.pop();
            Token2 = tQueue.front();
            if (Token1.GetType() == type) {
                return true; 
            }
            else {
                WhenFailed(Token1.linenumber());
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

void Parser::WhenFailed(int i) {
    cout << "Failure!" << "\n  (" << Token1.toString2() << ",\"" <<Token1.GetValue() <<"\"," << i << ")" << endl;
    failed = true;
    return;
}

Predicate Parser::ParseHeadPredicate() {
    Predicate headPredicate;
    if (failed == false) {
        parameters.clear();
        pCheck(ID);
        headPredicate.SetName(Token1.GetValue());
        pCheck(LEFT_PAREN);
        pCheck(ID);
        PushOnList(Token1.GetValue());
        ParseIDList();
        pCheck(RIGHT_PAREN);
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
            pCheck(COMMA);
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
        pCheck(ID);
        Predicates.SetName(Token1.GetValue());
        pCheck(LEFT_PAREN);
        newParam = ParseParameter();
        PushOnList(newParam.ToString());
        ParseParameterList();
        pCheck(RIGHT_PAREN);
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
            pCheck(STRING);
            newParam.SetParam(Token1.GetValue());
            return newParam;
        }   
        else if (Token2.GetType() == ID) {
            pCheck(ID);
            newParam.SetParam(Token1.GetValue());
            return newParam;
        }
        else if (Token2.GetType() == LEFT_PAREN) {
            string tempstring;
            tempstring = ParseExpression();
            tempstring = "(" + tempstring + ")";
            newParam.SetParam(tempstring);
            return newParam;
        }
        else {
            Token1 = Token2;
            Continue(ERROR);
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
            pCheck(COMMA);
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

        pCheck(LEFT_PAREN);
        newParam = ParseParameter();
        theExpression.SetRight(newParam);
        newParam.SetParam(ParseOperator().GetValue());
        theExpression.SetOperator(newParam);
        newParam = ParseParameter();
        theExpression.SetLeft(newParam);
        pCheck(RIGHT_PAREN);

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
            pCheck(ADD);
        }
        else if (Token2.GetType() == MULTIPLY) {
            pCheck(MULTIPLY);
        }
        else {
            pCheck(MULTIPLY);
        }
        return Token1;
    }
    else {
        return Token1;
    }
}
