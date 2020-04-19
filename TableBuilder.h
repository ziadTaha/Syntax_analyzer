//
// Created by zeny on 4/15/20.
//

#ifndef UNTITLED_TABLEBUILDER_H
#define UNTITLED_TABLEBUILDER_H
#include <bits/stdc++.h>
using namespace std;

class TableBuilder {
public:
    TableBuilder(unordered_map<string,set<string>>  &first, unordered_map<string,set<string>> &follow,unordered_map<string, set<string>> &productions);

    void build();
private:
    unordered_map<string,set<string>> first;

    unordered_map<string,set<string>> follow;

    unordered_map<string, set<string>>& productions;

    set<string> terminals;

    unordered_map<pair<string,string>, set<string>> &table;

    void calcTerminals();
};


#endif //UNTITLED_TABLEBUILDER_H