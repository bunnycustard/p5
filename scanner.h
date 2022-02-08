#pragma once
#include "token.h"
#include <fstream>
#include <queue>

enum state{init, WhiteSpaceState, CharState, SpecialState, FinalState, IDState, CommentState, StringState, EOFState};

class Scanner{
    protected:
        ifstream file;
        string fileName;
        char char1;
        char char2;
        int line1;
        state state1;
        string facts;
        bool char2val;

        Token states();
        string getWords();
        bool findWhiteSpace();

    public:
        Scanner(string inputfile);
        ~Scanner();

        void tokenize();
        queue <Token> GetList();
        queue <Token> tokens;
};
