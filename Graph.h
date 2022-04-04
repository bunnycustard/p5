#pragma once
#include <map>
#include <stack>
#include <iostream>
#include <vector>

#include "Node.h"
using namespace std;

class Graph{
    public:
    map<int, Node> nList;
    stack<int> topocate;
    vector<set<int>> scc;
    set<int> lSet;

    void dfs(Node Node1){
        if(Node1.punch == true){return;}
        else{
            nList.at(Node1.id).punch = true;
            for(auto i: Node1.adjcs){
                if(nList[i].punch == false){dfs(nList[i]);}
            }
            topocate.push(Node1.id);
            return;
        }
    }

    void dfsSCC(Node Node1){
        if(Node1.punch == true){return;}
        else{
            nList.at(Node1.id).punch = true;
            lSet.insert(Node1.id);
            for(auto i: Node1.adjcs){
                if(nList[i].punch == false){dfsSCC(nList[i]);}
            }
            return;
        }
    }

    void dfsF(){
        for (auto i: nList){
            if(i.second.punch == false){dfs(i.second);}
            else {}
        }
        return;
    }

    void dfsFF(){
        while(topocate.size() != 0){
            if(!nList[topocate.top()].punch){
                dfsSCC(nList[topocate.top()]);
            }
            else{
                if(lSet.size() != 0){
                    scc.push_back(lSet);
                    lSet.clear();
                }
                topocate.pop();
            }
        }
        return;
    }

    void addEdge(int from, int to, bool dependent){
        nList[from].adjcs.insert(to);
        nList[from].sustainable = dependent;
        return;
    }
    void ToString(){
        cout << "Dependency Graph" << endl;
        for(auto i:nList){
            cout << "R" << i.first << ":";
            int x = i.second.adjcs.size();
            int y = 0;
            for(auto j: i.second.adjcs){
                if (y != x - 1) {cout <<"R" << j <<",";}
                else {cout <<"R" << j;}
                y++;
            }
            cout << endl;
        }
        return;
    }

};
