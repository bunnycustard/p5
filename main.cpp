#include "scanner.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char* argv[]){
    if(!argv[1]){
        cout << "Include file name" << endl;
        cout << "Total Tokens = 0" << endl;
    }
    else{
        string filename = argv[1];
        Scanner Scanner1(filename);  
        Scanner1.tokenize();
        Parser Parser1;
				Interpreter Interpreter1;
        bool valid = Parser1.Logger(Scanner1.GetList());
        if(valid == false){Interpreter1.dlSet(Parser1.GetDatalog);}
    }
    return 0;
}
