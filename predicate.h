#pragma once
#include "parameter.h"
#include <vector>

class Predicate{
    public:
        void NameSetter(string theName);
        void PPush(Parameter theParameter);
        vector<Parameter> GetVec();
        string ToString();
		string nGet(){
			return Name;
		}
        vector<Parameter> paramlist;
        string Name;
};
