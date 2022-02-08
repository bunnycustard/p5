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
        Token Token1;
        if (char2val == true){
            char1 = char2;
            char2val = false;
        }
        else {char1 = file.get();}
        Token1 = states();
        if (!(findWhiteSpace())){
            if (Token1.GetType() == COMMENT){}
            else {tokens.push(Token1);}
        }
        else if(char1 == EOF){tokens.push(Token1);}
    }return;}

Token Scanner::states(){
	Token Token1;
	state1 = init;
	while(state1 != FinalState){
		switch(state1){
			case (init):
				if(char1 == EOF){state1 = EOFState;}
				else if(char1 == '#'){state1 = CommentState;}
				else if(char1 == '\''){state1 = StringState;}
				else if(isalpha(char1)){state1 = SpecialState;}
				else if(char1 == ','|| char1 == '.'|| char1 == '?'|| char1 == '('|| char1 == ')'|| char1 == '*'|| char1 == '+'|| char1 == ':'){state1 = CharState;}
				else if(findWhiteSpace()){
					if(char1 == '\n' || char1 == '\r'){
						line1++;
						state1 = WhiteSpaceState;
					}
					else if(char1 == '\t'){state1 = WhiteSpaceState;}
					state1 = WhiteSpaceState;
				} 
				else{
					string str;
					str += char1;
					Token1.Values2("UNDEFINED", str, line1);
					return Token1;
				}
				break;
				
			case (CharState): 
				if(char1 == ':'){
					char2 = file.get();
					if(char2 == '-'){
						Token1.Values1(":-", line1);
						return Token1;
					}
					else{
						Token1.Values1(":", line1);
						char2val = true;
						return Token1;
					}
				}
				else{
					string string1;
					string1 += char1;
					Token1.Values1(string1, line1);
					return Token1;
				}
				break;

			case (StringState):
				char1 = file.get();
				if (char1 == '\''){
					string str = "\'";
					int xline = 0;
					while(char1 != EOF){
						if(char1 == '\n' || char1 == '\r'){xline++;}
						char2 = file.peek();
						if(char1 == '\'' && char2 == '\''){
							char1 = file.get();
							char2 = file.peek();
							str = str + char1 + "\'";
						}
						else if(char1 == '\'' && char2 != '\''){
							str = str + "\'";
							Token1.Values2("STRING", str, line1);
							line1 = line1 + xline;
							return Token1;
							break;
						}
						else if(char2 == EOF){
							Token1.Values2("UNDEFINED", str, line1);
							tokens.push(Token1);
							Token1.Values1("EOF", line1 + xline);
							char1 = EOF;
							return Token1;
							break;
						}
						else{str = str + char1;}
						char1 = file.get();
					}
				}
				else if(char1 == '\''){
					Token1.Values2("STRING", "\'\'", line1);
					return Token1;
				}
				else{
					string str = "\'";
					int xline = 0;
					while(char1 != EOF){
						if(char1 == '\r' || char1 == '\n'){xline++;}
						char2 = file.peek();
						if(char1 == '\'' && char2 == '\''){
							char1 = file.get();
							char2 = file.peek();
							str = str + char1 + "\'";
						}
						else if(char1 == '\'' && char2 != '\''){
							str = str + "\'";
							Token1.Values2("STRING", str, line1);
							line1 = line1 + xline;
							return Token1;
							break;
						}
						else if(char2 == EOF){
							str += char1;
							Token1.Values2("UNDEFINED", str, line1);
							tokens.push(Token1);
							Token1.Values1("EOF", line1 + xline);
							char1 = EOF;
							return Token1;
							break;
						}
						else{str = str + char1;}
						char1 = file.get();
					}
				}
			break;

			case (CommentState):
				char2 = file.get();
				char1 = char2;
				if(char1 == '|'){
					int xline = 0;
					bool isEOF = false;
					string b;
					b = "#|";
					char1 = file.get();
					char2 = file.peek();
					while(char1 != EOF || char2 != EOF){
						if(char2 == '#' && char1 == '|'){
							b += "|#";
							file.get();
							Token1.Values2("COMMENT", b, line1);
							line1 =  line1 + xline;
							return Token1;
						}
						else if(char2 == EOF){isEOF = true;}

						if(char1 == '\r' || char1 == '\n'){
							xline = xline + 1;
							b.append("\n");
						}
						else{
							string temp;
							temp += char1;
							b.append(temp);
						}
						char1 = file.get();
						char2 = file.peek();
					}
					if(isEOF){
						Token1.Values2("UNDEFINED", b, line1);
						tokens.push(Token1);
						Token1.Values1("EOF", line1 + xline);
						char1 = EOF;
						return Token1;
					}
					else{
						Token1.Values2("COMMENT", b, line1);
						line1 = line1 + xline;
						Token1.toString();
						return Token1;
					}
					char1 = file.get();
				}
				else{
					string comment1 = "#";
					comment1 = comment1 + char1;
					char2 = file.peek();
					while(char2 != '\n'){
						char1 = file.get();
						comment1 = comment1 + char1;
						char2 = file.peek();
						if(char2 == '\r' || char2 =='\n'){break;}
					}
					Token1.Values2("COMMENT", comment1, line1);
					return Token1;
				}
			break;
			
			case (SpecialState):
				facts = getWords();
				if(char1 == 'F'){
					if(facts == "Facts"){
						Token1.Values1(facts, line1);
						return Token1;
					}
					else{state1 = IDState;}
				}
				else if(char1 == 'Q'){
					if(facts == "Queries"){
						Token1.Values1(facts, line1);
						return Token1;
					}
					else{state1 = IDState;}
				}
				else if(char1 == 'R'){
					if(facts == "Rules"){
						Token1.Values1(facts, line1);
						return Token1;
					}
					else{state1 = IDState;}
				}
				else if(char1 == 'S'){
					if(facts == "Schemes"){
						Token1.Values1(facts, line1);
						return Token1;
					}
					else{state1 = IDState;}
				}
				else{state1 = IDState;}
				break;

			case (IDState):
				Token1.Values2("ID", facts, line1);
				return Token1;
				break;
			case (EOFState):
				Token1.Values1("EOF", line1);
				return Token1;
				break;
			case (WhiteSpaceState):
				state1 = FinalState;
				break;
			case (FinalState):

				return Token1;
				break;
			default:
				Token1.Values2("UNDEFINED", "UNDEFINED", line1);
		}   
	}
	Token1.Values2("UNDEFINED", "UNDEFINED", line1);
	return Token1;
}

bool Scanner::findWhiteSpace(){
	if(char1 == ' ' || char1 == '\n' || char1 == '\r' || char1 == '\t'){return true;}
	else{return false;}
}

queue <Token> Scanner::GetList() {return tokens;}
