#include "token.h"
#include <sstream>

Token::Token(){
    value = "placeholder";
    line = -1;
    tType = ERROR;
}
Token::~Token(){}

int Token::linenumber(){return line;}

TokenType Token::GetType() {
    return tType;
}

string Token::toString(){
	string type = "placeholder";
	switch(tType){
		case COMMA:
			type = "COMMA";
			break;
		case PERIOD:
			type = "PERIOD";
			break;
		case Q_MARK:
			type = "Q_MARK";
			break;
		case LEFT_PAREN:
			type = "LEFT_PAREN";
			break;
		case RIGHT_PAREN:
			type = "RIGHT_PAREN";
			break;
		case COLON:
			type = "COLON";
			break;
		case COLON_DASH:
			type = "COLON_DASH";
			break;
		case MULTIPLY:
			type = "MULTIPLY";
			break;
		case ADD: 
			type = "ADD";
			break;
		case SCHEMES:
			type = "SCHEMES";
			break;
		case FACTS:
			type = "FACTS";
			break;
		case RULES:
			type = "RULES";
			break;
		case QUERIES:
			type = "QUERIES";
			break;
		case ID:
			type = "ID";
			break;
		case STRING:
			type = "STRING";
			break;
		case COMMENT:
			type = "COMMENT";
			break;
		case UNDEFINED:
			type = "UNDEFINED";
			break;
		case EOFa:
			type = "EOF";
			break;
		case ERROR:
			type = "ERROR";
	}
  stringstream out;
  out << "(" << type << "," << "\"" << value << "\"" << "," << to_string(line) << ")";
return out.str();
}

void Token::Values1(string myString ,int lineNum) {
        line = lineNum;
        value = myString;
    if (myString == ",") {
        tType = COMMA;
    }
    else if (myString == ".") {
        tType = PERIOD;
    }
    else if (myString == "?") {
        tType = Q_MARK;
    }
    else if (myString == "(") {
        tType = LEFT_PAREN;
    }
    else if (myString == ")") {
        tType = RIGHT_PAREN;
    }
    else if (myString == ":-") {
        tType = COLON_DASH;
    }
    else if (myString == ":") {
        tType = COLON;
    }
    else if (myString == "*") {
        tType = MULTIPLY;
    }
    else if (myString == "+") {
        tType = ADD;
    }
    else if (myString == "Schemes") {
        tType = SCHEMES;
    }
    else if (myString == "Facts") {
        tType = FACTS;
    }
    else if (myString == "Queries") {
        tType = QUERIES;
    }
    else if (myString == "Rules") {
        tType = RULES;
    }
    else if (myString == "EOF") {
        tType = EOFa;
        value = "";
    }
    //NEED TO ADD STRINGS AND COMMENTS and IDs
    else {
        tType = UNDEFINED;
    }

}

void Token::Values2 (string type, string token, int lineNum) {
    if (type == "ID") {
        tType = ID;
        value = token;
        line = lineNum;
    }
    else if ( type == "COMMENT") {
        tType = COMMENT;
        value = token; // may need to be modified
        line = lineNum;
    }
    else if (type == "STRING") {
        tType = STRING;
        value = token; // may need ot be modified
        line = lineNum;

    }
    else if (type == "UNDEFINED") {
        tType = UNDEFINED;
        value = token; // may need to be modified
        line = lineNum;

    }
}

string Token::TypeString() {
    string type = "ERROR1";
    switch (tType) {
        case COMMA:
            type = "COMMA";
            break;
        case PERIOD:
            type = "PERIOD";
            break;
        case Q_MARK:
            type = "Q_MARK";
            break;
        case LEFT_PAREN:
            type = "LEFT_PAREN";
            break;
        case RIGHT_PAREN:
            type = "RIGHT_PAREN";
            break;
        case COLON:
            type = "COLON";
            break;
        case COLON_DASH:
            type = "COLON_DASH";
            break;
        case MULTIPLY:
            type = "MULTIPLY";
            break;
        case ADD: 
            type = "ADD";
            break;
        case SCHEMES:
            type = "SCHEMES";
            break;
        case FACTS:
            type = "FACTS";
            break;
        case RULES:
            type = "RULES";
            break;
        case QUERIES:
            type = "QUERIES";
            break;
        case ID:
            type = "ID";
            break;
        case STRING:
            type = "STRING";
            break;
        case COMMENT:
            type = "COMMENT";
            break;
        case UNDEFINED:
            type = "UNDEFINED";
            break;
        case EOFa:
            type = "EOF";
            break;
        case ERROR:
            type = "ERROR";
        break;
    }
    return type;
}

string Token::GetValue() {
    return value;
}
