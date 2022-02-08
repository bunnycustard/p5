#pragma once
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

enum TokenType{COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, EOFa, ERROR};

class Token{
    protected:
        string value;
        int line;
        TokenType tType;

     public:
        Token();
        ~Token();
				
        string toString();
				string toString2();
        int linenumber();
        void Values1(string token, int line);
        void Values2(string type, string token, int line);
        TokenType GetType();
        string GetValue();
};
