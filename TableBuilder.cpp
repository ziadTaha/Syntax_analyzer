//
// Created by zeny on 4/15/20.
//

#include "TableBuilder.h"

#include <utility>


TableBuilder::TableBuilder(unordered_map<string, set<string>> &first, unordered_map<string, set<string>> &follow,
                           unordered_map<string, set<string>> &productions,
                           unordered_map<pair<string, string>, string, hash_pair> &table)
        : first (first), follow(follow), productions(productions), table(table) {

    calcTerminals();
}

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

void TableBuilder::build() {
    unordered_map<pair<string, string>, set<string>, hash_pair> t;
    for(auto production:this->productions){
        for(auto terminal:this->terminals){
            t[{production.first,terminal}]="error";
        }
        for(auto product:production.second){
            for(auto terminal:this->terminals){
                if(this->first[product].find(terminal) != this->first[product].end()){
                    t[{production.first,terminal}]=product;
                }if(this->follow[product].find(terminal) != this->follow[product].end()){
                    if(this->first[product].find("e") != this->first[product].end())
                        t[{production.first,terminal}]="e";
                    else
                        t[{production.first,terminal}]="synch";
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
