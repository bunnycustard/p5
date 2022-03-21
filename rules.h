#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Scheme{
	public:
	vector <string> values;
	unsigned int Size(){return values.size();}
	void sGet(vector<string> placeholder){values = placeholder;}
	string At(int i){return values.at(i);}
	void pBack(string appender){
		values.push_back(appender);
		return;
	}
	string Fake(){
		string opstr1;
		for(unsigned int i = 0; i < values.size(); i ++){opstr1 += values.at(i);}
		return opstr1;
	}
};
