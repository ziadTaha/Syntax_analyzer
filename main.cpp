#include <bits/stdc++.h>
#include <iostream>
#include "FollowMaker.h"
#include "FirstMaker.h"
#include "Parser.h"
#include "TableBuilder.h"

using namespace std ; 

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
    unordered_map<string, set<string>> pp = p.print() ;   
    FirstMaker fm = FirstMaker( pp);
    fm.make(); 
    fm.printin() ; 
    FollowMaker follow = FollowMaker( pp , fm.getF() );
    follow.setStart("METHOD_BODY");
    follow.make();
    follow.print();
    TableBuilder tb= TableBuilder(fm.getF(),follow.getFollow(), pp);
    tb.build();
    tb.print();
    tb.lastInput("METHOD_BODY");
    std::cout << "this is main!" << std::endl;
    return 0 ; 
}