#include "rules.h"

void Rule::HeadPredicateSetter(Predicate head){Head = head;}
void Rule::RuleSetter(vector<Predicate> T){
		for(unsigned int i = 0; i < T.size(); i++){RuleList.push_back(T.at(i));}
}
string Rule::ToString(){
    string Rule1;
    Rule1 = Head.ToString() + " :- ";
    for(unsigned int i = 0; i < RuleList.size(); i++){
        if( i == 0) {Rule1 = Rule1 + RuleList.at(i).ToString();}
        else{Rule1 = Rule1 + "," + RuleList.at(i).ToString();}
    } 
    Rule1 += ".";
    return Rule1;
}
