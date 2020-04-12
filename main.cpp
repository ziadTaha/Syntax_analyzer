#include <iostream>
#include "Parser.h"


int main() {
    Parser p ; 
    p.nonTerminal["non"] = { "a b B" , "a B B" , "c d g" , "c d e B" , "c d f B" , "a b f" , "b b b" , "a"}  ;   
    //p.nonTerminal["non"] = { "a b B" , "eee"  , "zzz" , "b B" , "b g" }  ;   
    p.leftFactoring() ; 
    p.print() ; 
    std::cout << "this is main!" << std::endl;
    return 0;
}
