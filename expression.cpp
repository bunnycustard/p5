#include "expression.h"

void Expression::LSetter(Parameter left){LP = left;}
void Expression::RSetter(Parameter right){RP = right;}
void Expression::OPSetter(Parameter oper){OP = oper;}

string Expression::ToString(){
    cout << "Expression to String" << endl;
    string out = "(" + RP.ToString() + OP.ToString() + LP.ToString() + ")";
    return out;
}
string Expression::EGet(){
    string E;
    E = RP.ToString() + OP.ToString() + LP.ToString();
    return E;
}
