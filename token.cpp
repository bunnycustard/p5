#include "token.h"
#include <sstream>

Token::Token(){
	value = "placeholder";
	line = -1;
	tType = ERROR;
}
Token::~Token(){}

int Token::linenumber(){return line;}
TokenType Token::GetType() {return tType;}

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

string Token::toString2(){
  string type = "ERROR1";
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
		break;
	}
  return type;
}

void Token::Values1(string input ,int linum){
	line = linum;
	value = input;

	if(input == ","){tType = COMMA;}
	else if(input == "."){tType = PERIOD;}
	else if(input == "?"){tType = Q_MARK;}
	else if(input == "("){tType = LEFT_PAREN;}
	else if(input == ")"){tType = RIGHT_PAREN;}
	else if(input == ":-"){tType = COLON_DASH;}
	else if(input == ":"){tType = COLON;}
	else if(input == "*"){tType = MULTIPLY;}
	else if(input == "+"){tType = ADD;}
	else if(input == "Schemes"){tType = SCHEMES;}
	else if(input == "Facts"){tType = FACTS;}
	else if(input == "Queries"){tType = QUERIES;}
	else if(input == "Rules"){tType = RULES;}
	else if(input == "String"){tType = STRING;}
	else if(input == "Comment"){tType = COMMENT;}
	else if(input == "ID"){tType = ID;}
	else if(input == "EOF"){
		tType = EOFa;
		value = "";
	}
	else{tType = UNDEFINED;}
}

void Token::Values2(string type, string token, int linum){
	if(type == "ID"){
		tType = ID;
		value = token;
		line = linum;
	}
	else if(type == "STRING"){
		tType = STRING;
		value = token;
		line = linum;
	}
	else if(type == "COMMENT"){
		tType = COMMENT;
		value = token;
		line = linum;
	}
	else if(type == "UNDEFINED"){
		tType = UNDEFINED;
		value = token;
		line = linum;
	}
}

string Token::GetValue(){return value;}
