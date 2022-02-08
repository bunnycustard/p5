#pragma once
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

enum TokenType{COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOFa, ERROR};

class Token{
    protected:
        string tokenValue;
        int line;
        TokenType tokenType;
     public:
        Token();
        ~Token();
        string toString();
        string TypeString();
        string GetValue();
        TokenType GetType();
        int linenumber();
        void SetValues(string token, int line);
        void SetComplexValues(string type, string token, int line);
};
