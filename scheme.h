#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Scheme{
	vector <string> values;
	public:
	unsigned int Size(){return values.size();}
	void sGet(vector<string> placeholder){values = 		 placeholder;}
	string At(int i){return values.at(i);}
	void pBack(string appender){
		values.push_back(appender);
		return;
	}
};
