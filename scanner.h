#pragma once
#include "token.h"
#include <fstream>
#include <queue>

enum state{init, WhiteSpaceState, CharState, SpecialState, FinalState, IDState, CommentState, StringState, EOFState};

class Scanner{
    protected:
        Token StateMachine();
        int LineGenerator();
        string WordExtractor();
        bool IsWhiteSpace();

        ifstream file;
        string fileName;
        char char1;
        char char2;
        int currentLine;
        state currentstate;
        string facts;
        bool char2val;

    public:
        Scanner(string nameOfFile);
        ~Scanner();
        void tokenize();
        queue <Token> GetList();

        queue <Token> tokenList;
};
