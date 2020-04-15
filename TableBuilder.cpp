//
// Created by zeny on 4/15/20.
//

#include "TableBuilder.h"

#include <utility>


TableBuilder::TableBuilder(unordered_map<string,set<string>> &first,unordered_map<string,set<string>> &follow,
unordered_map<string, set<string>> &productions):first (first), follow(follow), productions(productions){

    calcTerminals();
}

struct indx {
    string nt, t;  // First and last names

    indx(string nt, string t)
    {
        this->nt = std::move(nt);
        this->t=std::move(t);
    }

    //in case of collesions
    bool operator==(const indx& p) const
    {
        return nt == p.nt && t == p.t;
    }
};

class HashFunction {
public:

    size_t operator()(const indx& p) const
    {
        return (hash<string>()(p.nt)) ^
               (hash<string>()(p.t));
    }
};


void TableBuilder::calcTerminals() {

}

