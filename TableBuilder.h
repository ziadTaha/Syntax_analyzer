//
// Created by zeny on 4/15/20.
//

#ifndef UNTITLED_TABLEBUILDER_H
#define UNTITLED_TABLEBUILDER_H
#include <bits/stdc++.h>

using namespace std;

class TableBuilder {

private:
    unordered_map<string,set<string>> first;

    unordered_map<string,set<string>> follow;

    unordered_map<string, set<string>> productions;

    set<string> terminals;

    map<pair<string,string>, string> table;

    void calcTerminals();

    vector<string> tokenize(string s);

    bool isTerminal(string s);

public:
    TableBuilder(unordered_map<string, set<string>> first, unordered_map<string, set<string>> follow,
                 unordered_map<string, set<string>> productions);
    void build();
};


#endif //UNTITLED_TABLEBUILDER_H