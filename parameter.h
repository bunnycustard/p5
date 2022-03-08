#pragma once

#include "string"

using namespace std;

class Parameter{
	public:
		string P1
		bool boolString
		void ParamSetter(string param);
		string ToString();
		void BoolSetter(bool tf){
			boolString = tf
		}
		bool IsString(){
			return boolString;
		}
};
