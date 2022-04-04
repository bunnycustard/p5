#pragma once
#include <set>

class Node {
    public:
    std::set<int> adjcs;
    int id;
    bool punch;
    bool sustainable;
    Node(){
        punch = false;
    }
};
