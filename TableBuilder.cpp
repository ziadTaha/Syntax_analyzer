//
// Created by zeny on 4/15/20.
//

#include "TableBuilder.h"

#include <utility>


TableBuilder::TableBuilder(unordered_map<string, set<string>> first, unordered_map<string, set<string>> follow,
                           unordered_map<string, set<string>> productions)
        : first (first), follow(follow), productions(productions) {

    calcTerminals();
}

void TableBuilder::build() {
    map<pair<string,string>,string> t ={};
    for(auto production:this->productions){
        for(auto terminal:this->terminals){
            t[{production.first,terminal}]="error";
        }
        for(auto product:production.second){
            for(auto terminal:this->terminals){
                bool thisSlotIsTaken=false;
                if(this->first[product].find(terminal) != this->first[product].end()){
                    t[{production.first,terminal}]=product;thisSlotIsTaken=true;
                }if(this->follow[production.first].find(terminal) != this->follow[production.first].end()){                       //se if it can be [product]
                    if(this->first[production.first].find("e") != this->first[production.first].end()){
                        if(this->productions[production.first].find("e") != this->productions[production.first].end()&&
                           thisSlotIsTaken){
                            cout<<"multiple productions in one slot error !!";
                            break;
                        }
                        t[{production.first,terminal}]="e";
                    }
                    else{
                        t[{production.first,terminal}]="synch";
                    }
                }
            }
        }
    }
    this->table=t;
}

void TableBuilder::calcTerminals() {
    set<string>s;
    for( const auto& production:this->productions){
        for( const auto& product:production.second){
            vector<string>words=tokenize(product);
            for(const auto& word : words){
                if(isTerminal(word))
                    s.insert(word);
            }
        }
    }
    s.insert("$");
    this->terminals=s;
}

vector<string> TableBuilder::tokenize(string s) {
    // Vector of string to save tokens
    vector <string> tokens;

    // stringstream class check1
    stringstream check1(s);

    string intermediate;

    // Tokenizing w.r.t. space ' '
    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

bool TableBuilder::isTerminal(string s) {
    return (s[0]=='\''&&s[s.size()-1]=='\''&&s.find(' ')==string::npos);
}

