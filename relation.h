#pragma once
#include "scheme.h"
#include "tuple.h"
#include <set>

class Relation{
public:
    Relation(){}
    Scheme sGet(){return Scheme1;}
    set<Tuple> tGet(){return dTup;}
    int TupSize(){return dTup.size();}
    void ToString();
    set<Tuple> dTup;
    Relation select(int ind, string value);
    Relation select(int i1, int i2);
    Relation jects(vector<int> indicies);
    Relation declare(vector<string> names);
    void tAdd(Tuple tuples); 
    void sSet(Scheme dSch);
    void nSet(string dName);
    Relation Join(Relation relationToJoin);
    bool Unite(Relation toUnite);
    bool isJoinable(Tuple Tuple1, Tuple Tuple2Add, Scheme Scheme1, Scheme Scheme2Add);
    string name;
    Scheme Scheme1;
    bool BeenOutPutted;
};
