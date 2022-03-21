#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Tuple: public vector<string>{
	vector <string> values;
	bool beenOutputted;
	string At (int num) {
			return values.at(num);
	}
};
