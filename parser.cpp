#include "parser.h"

Parser::Parser(){}
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
    Schemes.push_back(pScheme());
    Schemes = pSchemeList(Schemes);
    if(failed == false){All.SchemesSetter(Schemes);}
    else{return All;}

    if(failed == false){
        pCheck(FACTS);
        pCheck(COLON);
        vector<Predicate> parsedFacts; 
        parsedFacts = pFactList(parsedFacts);
        if(failed == false){
            All.FactsSetter(parsedFacts);
            All.DomainSetter(Domain);
        }
        else{return All;}
    }
    else{return All;}

    if(failed == false){
        vector<Rule> Rules;
        pCheck(RULES);
        pCheck(COLON);
        Rules = pRuleList(Rules);
        if(failed == false){All.RulesSetter(Rules);}
        else{return All;}
    }
    else{return All;}
    if (failed == false){
        vector<Predicate> Queries;
        pCheck(QUERIES);
        pCheck(COLON);
        Queries.push_back(pQuery());
        Queries = pQueryList(Queries);
        if(failed == false){All.QueriesSetter(Queries);}
        else{return All;}
    }
    else{return All;}
    if(failed == false){
        if(Token2.GetType() == EOFa){
            cout << "Success!" << endl;
            return All;
        }
        else{
            while(Token2.GetType() != EOFa){
                Token1 = tQueue.front();
                tQueue.pop();
                Token2 = tQueue.front();
            }
            WhenFailed(Token1.linenumber());
            return All;
        }
    }
    else{return All;}
}

Predicate Parser::pQuery(){
    Predicate Query;
    if(failed == false){
        Query = pPredicate();
        pCheck(Q_MARK);
        return Query;
    }
    else{return Query;}
}

vector<Predicate> Parser::pQueryList(vector<Predicate> Queries){
    if(failed == false){
        if(Token2.GetType() != ID){return Queries;}
        else{
            Queries.push_back(pQuery());
            Queries = pQueryList(Queries);
            return Queries;
        }
    }
    else{return Queries;}
}

vector<Rule> Parser::pRuleList(vector<Rule> RuleList){
    if(failed == false){
        if(Token2.GetType() == QUERIES){return RuleList;}
        else{
            RuleList.push_back(pRules());
            RuleList = pRuleList(RuleList);
            return RuleList;
        }
    }
    else{return RuleList;}
}

Rule Parser::pRules(){
    Rule theRule;
    vector<Predicate> RulesList;
    Predicate rule;
    if(failed == false){
        theRule.HPSetter(pHeadPredicate());
        pCheck(COLON_DASH);
        rule = pPredicate();
        RulesList.push_back(rule);
        RulesList = pPredicateList(RulesList);
        pCheck(PERIOD);
        theRule.RuleSetter(RulesList);
        return theRule;
    }
    else{return theRule;}
}

vector<Predicate> Parser::pFactList(vector<Predicate> Facts){
    Predicate newFact;
    if(failed == false){
        if(Token2.GetType() == RULES){return Facts; }
        else{
            newFact = pFact();
            Facts.push_back(newFact);
            vector<Parameter> parameters;
            parameters = newFact.ReturnVector();
            for (unsigned int i = 0; i < parameters.size(); i++) {Domain.insert(parameters.at(i).ToString());}
            Facts = pFactList(Facts);
            return Facts;
        }
    }
    else{return Facts;}
}

Predicate Parser::pFact(){
    Predicate Facts;
    if(failed == false){
        parameters.clear();
        pCheck(ID);
        Facts.SetName(Token1.GetValue());
        pCheck(LEFT_PAREN);
        pCheck(STRING);
        Pusher(Token1.GetValue());
        Domain.insert(Token1.GetValue());
        pStringList();
        pCheck(RIGHT_PAREN);
        pCheck(PERIOD);
        for (unsigned int i = 0; i < parameters.size(); i++) {Facts.PushPredicate(parameters.at(i));}
        return Facts;
    }
    else{return Facts;} 
}

void Parser::pStringList(){
    if(failed == false){
        if(Token2.GetType() == COMMA){
            pCheck(COMMA);
            pCheck(STRING);
            Pusher(Token1.GetValue());
            pStringList();
        }
        else{return;}
    }
    else{return;}
}

Predicate Parser::pScheme(){
    Predicate Schemes;
    if(failed == false){
        parameters.clear();
        pCheck(ID);
        Schemes.SetName(Token1.GetValue());
        pCheck(LEFT_PAREN);
        pCheck(ID);
        Pusher(Token1.GetValue());
        pIDList();
        pCheck(RIGHT_PAREN);
        for(unsigned int i = 0; i < parameters.size(); i++){Schemes.PushPredicate(parameters.at(i));}
        return Schemes;
    }
    else{return Schemes;}
}

vector<Predicate> Parser::pSchemeList(vector<Predicate> Schemes){
    Predicate newScheme; 
    if(failed == false){
        if(Token2.GetType() == FACTS){return Schemes;}
        else{
            newScheme = pScheme();
            Schemes.push_back(newScheme);
            Schemes = pSchemeList(Schemes);
            return Schemes;
        }
    }
    else{return Schemes;}
}

void Parser::pIDList(){
    if(failed == false){
        if(Token2.GetType() == COMMA){
            pCheck(COMMA);
            pCheck(ID);
            Pusher(Token1.GetValue());
            pIDList();
        }
        else{return;}
    }
    else{return;}
}

bool Parser::Continue(TokenType type){
    if(failed == false){
        if(Token2.GetType() == type){return true;}
        else{
            WhenFailed(Token2.linenumber());
            return false;
        }
    }
    else{return false;}
}

bool Parser::pCheck(TokenType type){
    if(failed == false){
        if(Token2.GetType() != EOFa){
            Token1 = tQueue.front();
            tQueue.pop();
            Token2 = tQueue.front();
            if(Token1.GetType() == type){return true; }
            else{
                WhenFailed(Token1.linenumber());
                return false;
            }
        }
        else{
            Token1 = tQueue.front();
            return true;
        }
    }
    else{
        if(Token2.GetType() != EOFa){
            Token1 = tQueue.front();
            tQueue.pop();
            Token2 = tQueue.front();
        }
        else{Token1 = tQueue.front();}
        return false;
    }
}

void Parser::WhenFailed(int i){
    cout << "Failure!" << "\n  (" << Token1.toString2() << ",\"" <<Token1.GetValue() <<"\"," << i << ")" << endl;
    failed = true;
    return;
}

Predicate Parser::pHeadPredicate(){
    Predicate headPredicate;
    if(failed == false){
        parameters.clear();
        pCheck(ID);
        headPredicate.SetName(Token1.GetValue());
        pCheck(LEFT_PAREN);
        pCheck(ID);
        Pusher(Token1.GetValue());
        pIDList();
        pCheck(RIGHT_PAREN);
        for(unsigned int i = 0; i < parameters.size(); i++){headPredicate.PushPredicate(parameters.at(i));}
        return headPredicate;
    }
    else{return headPredicate;}
}

vector<Predicate> Parser::pPredicateList(vector<Predicate> list){
    if(failed == false){
        if(Token2.GetType() == COMMA){
            pCheck(COMMA);
            list.push_back(pPredicate());
            list = pPredicateList(list);
            return list;
        }
        else{return list;}
    }
    else{return list;}
}

Predicate Parser::pPredicate(){
    Predicate Predicates;
    Parameter Parameter2;
    if(failed == false){
        parameters.clear();
        pCheck(ID);
        Predicates.SetName(Token1.GetValue());
        pCheck(LEFT_PAREN);
        Parameter2 = pParameter();
        Pusher(Parameter2.ToString());
        pParameters();
        pCheck(RIGHT_PAREN);
        for(unsigned int i = 0; i < parameters.size(); i++){Predicates.PushPredicate(parameters.at(i));}
        return Predicates;
    }
    else{return Predicates;}
}

void Parser::Pusher(string token){
    Parameter Parameter2;
    if (Token1.GetValue() != ""){
        Parameter2.SetParam(token);
        parameters.push_back(Parameter2);
    }
    else{}
    return;
}

Parameter Parser::pParameter(){
    Parameter Parameter2;
    if(failed == false){
        Token toSend = Token2;
        if (Token2.GetType() == STRING){
            pCheck(STRING);
            Parameter2.SetParam(Token1.GetValue());
            return Parameter2;
        }   
        else if(Token2.GetType() == ID){
            pCheck(ID);
            Parameter2.SetParam(Token1.GetValue());
            return Parameter2;
        }
        else if(Token2.GetType() == LEFT_PAREN){
            string tempstring;
            tempstring = pExpression();
            tempstring = "(" + tempstring + ")";
            Parameter2.SetParam(tempstring);
            return Parameter2;
        }
        else{
            Token1 = Token2;
            Continue(ERROR);
            return Parameter2;
        }
    }
    else{return Parameter2;}
}

void Parser::pParameters(){
    if(failed == false){
        if(Token2.GetType() == RIGHT_PAREN){return;}
        else{
            Parameter Parameter2;
            pCheck(COMMA);
            Parameter2 = pParameter();
            Pusher(Parameter2.ToString());
            pParameters();
            return;
        }
    }
    else{return;}
}

string Parser::pExpression(){
    if(failed == false){
        Expression theExpression;
        Parameter Parameter2;

        pCheck(LEFT_PAREN);
        Parameter2 = pParameter();
        theExpression.SetRight(Parameter2);
        Parameter2.SetParam(pOperator().GetValue());
        theExpression.SetOperator(Parameter2);
        Parameter2 = pParameter();
        theExpression.SetLeft(Parameter2);
        pCheck(RIGHT_PAREN);

        return theExpression.GetExpression();
    }
    else{
        string list;
        return list;
    }
}

Token Parser::pOperator(){
    if(failed == false){
        if(Token2.GetType() == ADD){pCheck(ADD);}
        else if(Token2.GetType() == MULTIPLY){pCheck(MULTIPLY);}
        else{pCheck(MULTIPLY);}
        return Token1;
    }
    else{return Token1;}
}
