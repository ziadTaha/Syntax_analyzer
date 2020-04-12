#include <iostream>
#include<bits/stdc++.h> 

using namespace std ; 
class Parser
{
private:
    /* data */
    unordered_map <string , vector <string> > nonTerminal ;
    void readGrammer (string path) ; 
    vector<string > stringToVector(string s) ;  
    void leftFactoring () ; 
    

public:
    Parser(/* args */);
    ~Parser();
    int trying  ; 
};

