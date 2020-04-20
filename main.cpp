#include <iostream>

#include "Parser.h"


int main() {
    Parser p ; 
    //p.nonTerminal["non"] = { "a b B" , "a B B" , "c d g" , "c d e B" , "c d f B" , "a b f" , "b b b" , "a"}  ;   
    //p.nonTerminal["non"] = { "a b B" , "eee"  , "zzz" , "b B" , "b g" }  ;   
    //p.nonTerminal["S"]={"A a","b"};
    //p.nonTerminal["A"]={"A c","S d","f"};
    //p.leftRecursion();
    //p.leftFactoring() ;
    p.readGrammer("input.txt") ; 
    p.leftRecursion();
    p.leftFactoring() ;  
    p.print() ; 
    std::cout << "this is main!" << std::endl;
}
/*=======
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
>>>>>>> 384e23eba9a05e9e46d8b96bb76645e10252a1aa
    return 0;
}
*/