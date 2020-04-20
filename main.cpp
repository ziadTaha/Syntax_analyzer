#include <iostream>
#include <bits/stdc++.h>
#include "FirstMaker.h"
#include "FollowMaker.h"

using namespace std;

int main() {

    //constructing the productions manually
    unordered_map<string, set<string>> p;   //5   //6        //7  //8   //9         //10       //11
    vector<string>l={"E","E'","T","T'","F","T E'","'+' T E'","eeee","F T'","'*' F T'","'(' E ')'","'id'"};
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

    FollowMaker follow = FollowMaker(p,fm.getF());
    follow.setStart("E");
    follow.make();


    cout << "n" << std::endl;
    return 0;
}
