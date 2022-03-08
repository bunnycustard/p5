#pragma once
#include "parameter.h"
#include <vector>

class Predicate{
    private:
        vector<Parameter> paramlist;
        string Name;
    public:
        void NameSetter(string theName);
        void PPush(Parameter theParameter);
        vector<Parameter> GetVec();
        string ToString();
		string nGet(){
			return Name;
		}
};
