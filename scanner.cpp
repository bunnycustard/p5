#include "scanner.h"
#include "token.h"
#include <fstream>
#include <cctype>
#include <cstdio> 
#include <sstream> 

Scanner::Scanner(string inputfile) {
    fileName = inputfile;
    char1 = '=';
    char2 = '=';
    line1 = 1;
    state1 = init;
    file.open(fileName);
    facts = "==";
}
Scanner::~Scanner() {file.close();}

string Scanner::getWords(){
	char tempChar;
	string Word1;
	Word1 += char1;  
	tempChar = file.get();

	while(isdigit(tempChar) || isalpha(tempChar)){
		Word1 = Word1 + tempChar;
		tempChar = file.get();  
	}
	if((!isdigit(tempChar)) && !isalpha(tempChar)){
		char2val = true;
		char2 = tempChar;
	}            
	return Word1;
}

void Scanner::tokenize(){
    while (file.good()){
        Token newToken;
        if (char2val == true){
            char1 = char2;
            char2val = false;
        }
        else {char1 = file.get();}
        newToken = states();
        if (!(findWhiteSpace())){
            if (newToken.GetType() == COMMENT){}
            else {tokens.push(newToken);}
        }
        else if(char1 == EOF){tokens.push(newToken);}
    }return;}

Token Scanner::states() {
    Token newToken;
    state1 = init;
    while (state1 != FinalState) {
        switch(state1) {
            case (init):
                if(char1 == EOF){
                    state1 = EOFState;
                }
                else if (char1 == ','|| char1 == '.'|| char1 == '?'||
                    char1 == '('|| char1 == ')'|| char1 == '*'||
                    char1 == '+'|| char1 == ':') {
                    state1 = CharState; 
                }
                else if (findWhiteSpace()) {
                    if (char1 == '\n'|| char1 == '\r') {
                        line1++;
                        state1 = WhiteSpaceState;
                    }
                    else if (char1 == '\t') {
                        state1 = WhiteSpaceState;
                    }
                    state1 = WhiteSpaceState;
                } 
                else if (char1 == '#') {
                    state1 = CommentState;
                }
                else if (char1 == '\'') {
                    state1 = StringState;
                }
                else if (isalpha(char1)) {
                    state1 = SpecialState;
                }
                else {
                    string mstr;
                    mstr += char1;
                    newToken.Values2("UNDEFINED", mstr, line1);
                    return newToken;
                }
                break;

            case (CharState): 
                if (char1 == ':') {
                    char2 = file.get();
                    if (char2 == '-') {
                        newToken.Values1(":-", line1);
                        return newToken;
                    }
                    else {
                        newToken.Values1(":", line1);
                        char2val = true;
                        return newToken;
                    }
                }
                else {
                    string mystring;
                    mystring += char1;
                    newToken.Values1(mystring, line1);
                    return newToken;
                }
                break;

            case (SpecialState):
                facts = getWords();
                if (char1 == 'F') {
                    if (facts == "Facts") {
                        newToken.Values1(facts, line1);
                        return newToken;
                    }
                    else {
                        state1 = IDState;
                    }
                }
                else if (char1 == 'S') {
                    if (facts == "Schemes") {
                        newToken.Values1(facts, line1);
                        return newToken;
                    }
                    else {
                        state1 = IDState;
                    }
                }
                else if (char1 == 'Q') {
                    if (facts == "Queries") {
                        newToken.Values1(facts, line1);
                        return newToken;
                    }
                    else {
                        state1 = IDState;
                    }
                }
                else if (char1 == 'R') {
                    if (facts == "Rules") {
                        newToken.Values1(facts, line1);
                        return newToken;
                    }
                    else {
                        state1 = IDState;
                    }
                }
                else {
                    state1 = IDState;
                }
                break;

            case (CommentState)://---------------------------------------------------CommentState-------------------------------------------------
                char2 = file.get();
                char1 = char2;
                if (char1 == '|') {
                    int otherlines = 0;
                    bool isEOF = false;
                    string bcom;
                    bcom = "#|";
                    char1 = file.get();
                    char2 = file.peek();
                    while (char1 != EOF || char2 != EOF) {
                        if (char2 == '#' && char1 == '|') {
                            bcom += "|#";
                            file.get();
                            newToken.Values2("COMMENT", bcom, line1);
                            line1 =  line1 + otherlines;
                            return newToken;
                        }
                        else if (char2 == EOF) {
                            isEOF = true;
                        }

                        if (char1 == '\r' || char1 == '\n'){
                            otherlines = otherlines + 1;
                            bcom.append("\n");
                        }
                        else {
                            string cool;
                            cool += char1;
                            bcom.append(cool);
                        }
                        char1 = file.get();
                        char2 = file.peek();
                    }
                    if (isEOF) {
                        newToken.Values2("UNDEFINED", bcom, line1);
                        tokens.push(newToken);
                        newToken.Values1("EOF", line1 + otherlines);
                        char1 = EOF;
                       return newToken;
                    }
                    else {
                        newToken.Values2("COMMENT", bcom, line1);
                        line1 = line1 + otherlines;
                        newToken.toString();
                        return newToken;
                    }
                    char1 = file.get();
                }
                else {
                    string comment = "#";
                    comment = comment + char1;
                    char2 = file.peek();
                    while (char2 != '\n') {
                        char1 = file.get();
                        comment = comment + char1;
                        char2 = file.peek();
                        if (char2 == '\r' || char2 =='\n') {
                            break;
                        }
                    }
                    newToken.Values2("COMMENT", comment, line1);
                    return newToken;
                }
                
                
            break;
            case (StringState)://-----------------------------------------------------StringState CASE -------------------------------------
                char1 = file.get();
                if (char1 == '\'') {
                    string mstr = "\'";
                    int otherlines = 0;
                    while (char1 != EOF) {
                        if (char1 == '\r' || char1 == '\n') {
                            otherlines++;
                        }
                        char2 = file.peek();
                        if (char1 == '\'' && char2 == '\'') {
                            char1 = file.get();
                            char2 = file.peek();
                            mstr = mstr + char1 + "\'";

                        }
                        else if (char1 == '\'' && char2 != '\''){
                            mstr = mstr + "\'";
                            newToken.Values2("STRING", mstr, line1);
                            line1 = line1 + otherlines;
                            return newToken;
                            break;
                        }
                        else if (char2 == EOF) {
                            newToken.Values2("UNDEFINED", mstr, line1);
                            tokens.push(newToken);
                            newToken.Values1("EOF", line1 + otherlines);
                            char1 = EOF;
                            return newToken;
                            break;
                        }
                        else {
                            mstr = mstr + char1;
                        }
                        char1 = file.get();
                    }
                }
                else if (char1 == '\'') {
                    newToken.Values2("STRING", "\'\'", line1);
                    return newToken;
                }
                else {
                    string mstr = "\'";
                    int otherlines = 0;
                    while (char1 != EOF) {
                        if (char1 == '\r' || char1 == '\n') {
                            otherlines++;
                        }
                        char2 = file.peek();
                        if (char1 == '\'' && char2 == '\'') {
                            char1 = file.get();
                            char2 = file.peek();
                            mstr = mstr + char1 + "\'";

                        }
                        else if (char1 == '\'' && char2 != '\''){
                            mstr = mstr + "\'";
                            newToken.Values2("STRING", mstr, line1);
                            line1 = line1 + otherlines;
                            return newToken;
                            break;
                        }
                        else if (char2 == EOF) {
                            mstr += char1;
                            newToken.Values2("UNDEFINED", mstr, line1);
                            tokens.push(newToken);
                            newToken.Values1("EOF", line1 + otherlines);
                            char1 = EOF;
                            return newToken;
                            break;
                        }
                        else {
                            mstr = mstr + char1;
                        }
                        char1 = file.get();
                    }
                }
            break;
            case (IDState):
                newToken.Values2("ID", facts, line1);
                return newToken;
                break;
            case (EOFState):
                newToken.Values1("EOF", line1);
                return newToken;
                break;
            case (WhiteSpaceState):
                state1 = FinalState;
                break;
            case (FinalState):
                return newToken;
                break;
            default:
                newToken.Values2("UNDEFINED", "UNDEFINED", line1);
        }   
    }
    newToken.Values2("UNDEFINED", "UNDEFINED", line1);
    return newToken;
}

bool Scanner::findWhiteSpace(){
	if(char1 == ' ' || char1 == '\n' || char1 == '\r' || char1 == '\t'){return true;}
	else{return false;}
}

queue <Token> Scanner::GetList() {return tokens;}
