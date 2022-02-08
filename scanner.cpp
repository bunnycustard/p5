#include "scanner.h"
#include "token.h"
#include <fstream>
#include <cctype>
#include <cstdio> 
#include <sstream> 
// it is having trouble with the initial condition compiling them more than once

Scanner::Scanner(string nameOfFile) {
    fileName = nameOfFile;
    char1 = '=';
    char2 = '=';
    currentLine = 1;
    currentstate = init;
    file.open(fileName);
    facts = "==";
    //initial = 1;
}

Scanner::~Scanner() {
    file.close();
}

bool Scanner::IsWhiteSpace() {
    if (char1 == ' ' || char1 == '\t' || char1 == '\n' || char1 == '\r') {
        return true;
    }
    else {
        return false;
    }
}


string Scanner::WordExtractor() {
    string newWord;
    char wordChar;
    newWord += char1;  
    wordChar = file.get();
    while(isalpha(wordChar)||isdigit(wordChar)) {
        newWord = newWord + wordChar;
        wordChar = file.get();  
    }
    if (!(isalpha(wordChar)) && !isdigit(wordChar)) {
        char2val = true;
        char2 = wordChar;
    }            
    return newWord;
}

int Scanner::LineGenerator() {
    currentLine++;
    return currentLine;
}

void Scanner::tokenize() {
    while (file.good()) {
        Token newToken;
        if (char2val == true) {
            char1 = char2;
            char2val = false;
        }
        else {
            char1 = file.get();
        }
        newToken = StateMachine();
        if /*(*/(!(IsWhiteSpace()) /*&& initial == 0)*/) { // change to newline and stuff that doesn't make a token
            if (newToken.GetType() == COMMENT) {
                //cout << "Comment Ignored" << endl;
            }
            else {
                tokenList.push(newToken);
            }
        }
        else if (char1 == EOF) {
            tokenList.push(newToken);
        }
        //initial = 0;
    }
    return;
}

Token Scanner::StateMachine() {
    Token newToken;
    currentstate = init;
    while (currentstate != FinalState) {
        switch(currentstate) {
            case (init): // ----------------------------------------------- init CASE ---------------------------------------------------
                if(char1 == EOF){
                    currentstate = EOFState;
                }
                /*
                else if (initial == 1) {
                    currentstate = FinalState;
                }
                */
                else if (char1 == ','|| char1 == '.'|| char1 == '?'||
                    char1 == '('|| char1 == ')'|| char1 == '*'||
                    char1 == '+'|| char1 == ':') {
                    currentstate = CharState; 
                }
                else if (IsWhiteSpace()) {
                    if (char1 == '\n'|| char1 == '\r') {
                        currentLine++;
                        currentstate = WhiteSpaceState;
                    }
                    else if (char1 == '\t') {
                        currentstate = WhiteSpaceState;
                    }
                    currentstate = WhiteSpaceState;
                } 
                else if (char1 == '#') {
                    currentstate = CommentState;
                }
                else if (char1 == '\'') {
                    currentstate = StringState;
                }
                else if (isalpha(char1)) {
                    currentstate = SpecialState;
                }
                else {
                    string mstr;
                    mstr += char1;
                    newToken.Values2("UNDEFINED", mstr, currentLine);
                    return newToken;
                }
                break;

            case (CharState): //----------------------------------------------- CharState CASE -----------------------------------------------------
            // ---------------------------------------- Identifies ":" ":-" "," "." "(" ")" "*" "+" ----------------------------------------
                if (char1 == ':') {
                    char2 = file.get();
                    if (char2 == '-') {
                        newToken.Values1(":-", currentLine);
                        return newToken;
                    }
                    else {
                        newToken.Values1(":", currentLine);
                        char2val = true;
                        return newToken;
                    }
                }
                else {
                    string mystring;
                    mystring += char1;
                    newToken.Values1(mystring, currentLine);
                    return newToken;
                }
                break;

            case (SpecialState): // ----------------------------------------- SpecialState CASE ----------------------------------------------------
            // -----------------------------------------------I dentifies the "Facts", "Queries", "Rules", "Schemes" -----------------------
                facts = WordExtractor();
                if (char1 == 'F') { // THIS IS TO IDENTIFY THE FACTS KEYWORD
                    if (facts == "Facts") {
                        newToken.Values1(facts, currentLine);
                        return newToken;
                    }
                    else {
                        currentstate = IDState;
                    }
                }
                else if (char1 == 'S') { // THIS IS TO IDENTIFY THE SCHEMES KEYWORD
                    if (facts == "Schemes") {
                        newToken.Values1(facts, currentLine);
                        return newToken;
                    }
                    else {
                        currentstate = IDState;
                    }
                }
                else if (char1 == 'Q') { // THIS IS TO IDENTIFY THE QUERIES KEYWORD
                    if (facts == "Queries") {
                        newToken.Values1(facts, currentLine);
                        return newToken;
                    }
                    else {
                        currentstate = IDState;
                    }
                }
                else if (char1 == 'R') { // THIS IS TO IDENTIFY THE RULES KEY WORD
                    if (facts == "Rules") {
                        newToken.Values1(facts, currentLine);
                        return newToken;
                    }
                    else {
                        currentstate = IDState;
                    }
                }
                else {
                    currentstate = IDState;
                }
                break;

            case (CommentState)://---------------------------------------------------CommentState-------------------------------------------------
            // not working for the special case that it reaches the end without getting the closing comment identifier
                char2 = file.get();
                //block comment
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
                            newToken.Values2("COMMENT", bcom, currentLine);
                            currentLine =  currentLine + otherlines;
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
                        newToken.Values2("UNDEFINED", bcom, currentLine);
                        tokenList.push(newToken);//////////////////////////////////////////////////////////////////////////////////////////////
                        newToken.Values1("EOF", currentLine + otherlines);/////////////////////////////////////////////////////////////////////////////////
                        char1 = EOF;
                       return newToken;
                    }
                    else {
                        newToken.Values2("COMMENT", bcom, currentLine);
                        currentLine = currentLine + otherlines;
                        newToken.toString();
                        return newToken;
                    }
                    char1 = file.get();
                }
                //line comment
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
                    newToken.Values2("COMMENT", comment, currentLine);
                    return newToken;
                }
                
                
            break;
            case (StringState)://-----------------------------------------------------StringState CASE -------------------------------------
                char1 = file.get();
                //general case: goes until reaches another '
                if (char1 == '\'') {
                    string mstr = "\'";
                    int otherlines = 0;
                    while (char1 != EOF) {
                        if (char1 == '\r' || char1 == '\n') {
                            otherlines++;
                        }
                        char2 = file.peek();
                        if (char1 == '\'' && char2 == '\'') { // special case that back to back '' are found
                            char1 = file.get();
                            char2 = file.peek();
                            mstr = mstr + char1 + "\'";

                        }
                        else if (char1 == '\'' && char2 != '\''){  // single ' is found
                            mstr = mstr + "\'";
                            newToken.Values2("STRING", mstr, currentLine);
                            currentLine = currentLine + otherlines;
                            return newToken;
                            break;
                        }
                        else if (char2 == EOF) {
                            newToken.Values2("UNDEFINED", mstr, currentLine);
                            tokenList.push(newToken);/////////////////////////////////////////////////////////////////////
                            newToken.Values1("EOF", currentLine + otherlines);////////////////////////////////////////////////////////
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
                    newToken.Values2("STRING", "\'\'", currentLine);
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
                        if (char1 == '\'' && char2 == '\'') { // special case that back to back '' are found
                            char1 = file.get();
                            char2 = file.peek();
                            mstr = mstr + char1 + "\'";

                        }
                        else if (char1 == '\'' && char2 != '\''){  // single ' is found
                            mstr = mstr + "\'";
                            newToken.Values2("STRING", mstr, currentLine);
                            currentLine = currentLine + otherlines;
                            return newToken;
                            break;
                        }
                        else if (char2 == EOF) {
                            mstr += char1;
                            newToken.Values2("UNDEFINED", mstr, currentLine);
                            tokenList.push(newToken);/////////////////////////////////////////////////////////////////////
                            newToken.Values1("EOF", currentLine + otherlines);////////////////////////////////////////////////////////
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
            case (IDState): //---------------------------------------------------------- IDState CASE ---------------------------------------
                newToken.Values2("ID", facts, currentLine);
                return newToken;
                break;
            case (EOFState): // -------------------------------------------------------- EOF CASE ---------------------------------------
                newToken.Values1("EOF", currentLine);
                return newToken;
                break;
            case (WhiteSpaceState): //-------------------------------------------------- WhiteSpace CASE --------------------------------
                currentstate = FinalState;
                break;
            case (FinalState): // ------------------------------------------------------ FinalState CASE ------------------------------------
                return newToken;
                break;
            default:
                newToken.Values2("UNDEFINED", "UNDEFINED", currentLine);
        }   
    }
    newToken.Values2("UNDEFINED", "UNDEFINED", currentLine);
    return newToken;
}

queue <Token> Scanner::GetList() {
    return tokenList;
}
