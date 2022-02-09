#include "scanner.h"
#include "parser.h"

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
        bool valid = Parser1.Logger(Scanner1.GetList());
        if(valid == false){Parser1.ToString();}
    }
    return 0;
}
