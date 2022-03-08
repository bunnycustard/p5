#pragma once
#include <map>
#include "relation.h"

class Database{
public:
    map<string, Relation> dbs;
    void rAdd(string Name, Relation Relation1){
        dbs.insert({Name, Relation1});
        return;
    }
    void tAddr(string Name, Tuple Tuple1){
        dbs.at(Name).tAdd(Tuple1);
        return;
    }
    string ToStirng() {
        string opstr1;
        map<string, Relation> ptr;
        for (auto i: dbs) {opstr1  =  i.first + ": \n" + i.second.ToString();}
        return opstr1;
    }
    Relation GetRelation(string Name){return dbs.at(Name);}
};
