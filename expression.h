#include <vector>

#include "token.h"
#include "parameter.h"

class Expression{
private:
    Parameter LP;
    Parameter RP;
    Parameter OP;
public:
    void LSetter(Parameter left);
    void RSetter(Parameter right);
    void OPSetter(Parameter oper);
		
    string EGet();
    string ToString();
};
