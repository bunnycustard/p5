#pragma once
#include "scheme.h"
#include "tuple.h"
#include <set>

class Relation{
private:
    string name;
    Scheme Scheme1;
public:
    Relation(){}
    Scheme sGet(){return Scheme1;}
    set<Tuple> tGet() {return dTup;}
    string ToString();
    set<Tuple> dTup;
    Relation select(int ind, string value);
    Relation select(int i1, int i2);
    Relation jects(vector<int> indicies);
    Relation declare(vector<string> names);
    void tAdd(Tuple tuples); 
    void sSet(Scheme dSch);
    void nSet(string dName);
};
