#include <iostream>
#include "Parser.h"


int main() {
    Parser p ; 
    p.nonTerminal["1"] = { "a b B" , "a B" , "c d g" , "c d e B" , "c d f B" , "a b f"}  ;   
    p.leftFactoring() ; 
    std::cout << "this is main!" << std::endl;
    return 0;
}
