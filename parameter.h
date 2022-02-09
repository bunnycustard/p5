#pragma once

#include "string"

using namespace std;

class Parameter{
    private:
        string P1;
    public:
        void ParamSetter(string param);
        string ToString();
};
