#include <iostream>
#include <bits/stdc++.h>
#include "FirstMaker.h"
#include "TableBuilder.h"
using namespace std;

int main() {

    //constructing the productions manually
    unordered_map<string, set<string>> p;   //5   //6        //7  //8   //9         //10       //11
    vector<string>l={"E","E'","T","T'","F","T E'","'+' T E'","e","F T'","'*' F T'","'(' E ')'","'id'"};
    set<string> s;

    s.insert(l[5]);
    p[l[0]]=s;

    s.clear();

    s.insert(l[6]);
    s.insert(l[7]);
    p[l[1]]=s;

    s.clear();

    s.insert(l[8]);
    p[l[2]]=s;

    s.clear();

    s.insert(l[9]);
    s.insert(l[7]);
    p[l[3]]=s;

    s.clear();

    s.insert(l[10]);
    s.insert(l[11]);
    p[l[4]]=s;

    s.clear();

    //trying the first maker
    FirstMaker fm=FirstMaker(p);
    fm.make();

    //constructing the follow set manually
    unordered_map<string, set<string>> follow;
    s.insert("$");
    s.insert(")");
    follow[l[0]]=s;
    follow[l[1]]=s;
    s.insert("+");
    follow[l[2]]=s;
    follow[l[3]]=s;
    s.insert("*");
    follow[l[4]]=s;

    //trying the table builder
    TableBuilder tb= TableBuilder(fm.getF(),follow,p);
    tb.build();

    cout << "n" << std::endl;
    return 0;
}
