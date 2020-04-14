#include <iostream>
#include<bits/stdc++.h> 

using namespace std ; 
class Parser
{
private:
    /* data */
    
    void readGrammer (string path) ; 

    vector<string > stringToVector(string s) ;  
    string vectorToString(vector<string > vec);
    void immediateLeftRecursion(string a,vector <string> ex);
    void replaceAwithB(string a,string b);

    vector<string> oring( string s) ;

    

public:
    Parser(/* args */);
    ~Parser();
    int trying  ; 
    map <string , vector <string> > nonTerminal ;
    void leftRecursion () ; 
    void leftFactoring () ; 
    void print() ; 
    
};

