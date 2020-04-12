#include <iostream>
#include<bits/stdc++.h> 

using namespace std ; 
class Parser
{
private:
    /* data */
    
    void readGrammer (string path) ; 
    vector<string> stringToVector(string s) ;  
    vector<string> oring( string s) ;
    

public:
    Parser(/* args */);
    ~Parser();
    int trying  ; 
    unordered_map <string , vector <string> > nonTerminal ;
    void leftFactoring () ; 
    void print() ; 
};

