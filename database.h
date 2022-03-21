#pragma once
#include <map>
#include <sstream>
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
        stringstream opstr1;
        map<string, Relation> ptr;
        for (auto i: dbs) {
					cout  <<  i.first << ": \n";
          i.second.ToString();
				}
        return opstr1.str();
    }
    Relation GetRelation(string Name){return dbs.at(Name);}
    int TQ() {
        int size = 0;
        for (auto i: dbs) {
            cout << "This is the Size: ";
            size += i.second.TupSize();
            cout << size << endl;
        }
        return size;
    }
};
