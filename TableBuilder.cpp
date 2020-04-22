//
// Created by zeny on 4/15/20.
//

#include "TableBuilder.h"

#include <utility>


TableBuilder::TableBuilder(unordered_map<string, set<string>> first, unordered_map<string, set<string>> follow,
                           unordered_map<string, set<string>> productions)
        : first (first), follow(follow), productions(productions) {

    calcTerminals();
}

void TableBuilder::build() {
    map<pair<string,string>,string> t ={};
    for(auto production:this->productions){
        for(auto terminal:this->terminals){
            t[{production.first,terminal}]="error";
        }
        for(auto product:production.second){
            for(auto terminal:this->terminals){
                bool thisSlotIsTaken=false;
                if(this->first[product].find(terminal) != this->first[product].end()){
                    t[{production.first,terminal}]=product;thisSlotIsTaken=true;
                }
                if(this->follow[production.first].find(terminal) != this->follow[production.first].end()){                       //se if it can be [product]
                    if(this->first[production.first].find("eeee") != this->first[production.first].end()){
                        if(this->productions[production.first].find("eeee") != this->productions[production.first].end()&&
                           thisSlotIsTaken){
                            cout<<"multiple productions in one slot error !!" << endl ;
                            break;
                        }
                        t[{production.first,terminal}]="eeee";
                    }
                     else if (t[{production.first,terminal}] == "error"){
                        t[{production.first,terminal}]="synch";
                    }
                }
            }
        }
    }
    this->table=t;
}

void TableBuilder::calcTerminals() {
    set<string>s;
    for( const auto& production:this->productions){
        for( const auto& product:production.second){
            vector<string>words=tokenize(product);
            for(const auto& word : words){
                if(isTerminal(word)){
                    s.insert(word);
                }
            }
        }
    }
   s.insert("\'$\'");
    this->terminals=s;
}

vector<string> TableBuilder::tokenize(string s) {
    // Vector of string to save tokens
    vector <string> tokens;

    // stringstream class check1
    stringstream check1(s);

    string intermediate;
    // Tokenizing w.r.t. space ' '
    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

bool TableBuilder::isTerminal(string s) {
    return (s[0]=='\''&&s[s.size()-1]=='\''&&s.find(' ')==string::npos);

}
/*
bool TableBuilder::isTerminal(string s) {
    return (s[0]=='\''&&s[s.size()-1]=='\''&&s.find(' ')==string::npos);
}
*/
void TableBuilder::lastInput(string firstNon) {
   
    vector<string> inputWords ; 
   
   // reading input 
    fstream file; 
    string word, t, q, filename; 
    filename = "outputPhase1.txt"; 
    file.open(filename.c_str()); 
  
    while (file >> word) 
    { 
        word = "\'" + word + "\'" ; 
       inputWords.push_back(word) ; 
    } 

    // ---------- 
    stack <string>  s ; 
    s.push("\'$\'") ;  
    s.push(firstNon) ; 
    inputWords.push_back("\'$\'") ;  
    int i = 0 ; 
    while (!s.empty() && i < inputWords.size())
    {
        string stackP = s.top() ; 
        s.pop() ;
      //  cout << "ssss "  << stackP << " " << i << " " << inputWords[i] << endl ; 
        if (stackP == "synch") {
            cout << "error synch \n" ;
            continue ;  
        }

        if (stackP == "eeee") {
            continue ;  
        }

        if (!isTerminal(stackP)){
          // may the string from table must spilt
          if ( table[{ stackP , inputWords[i] }] != "" ){ 
            vector <string> ss  =  tokenize( table[{ stackP , inputWords[i] }]) ;
            for ( int j = ss.size() -1 ; j >= 0 ; j-- ){
                if (ss[j] != " " && ss[j] != "")
                 s.push(ss[j]) ;
            }
          }
          else
          {
               cout << "error in table\n"  ;
               cout << "Www " << stackP << " ff " << inputWords[i] << endl ;  
               continue ; 
          }
           
          // handel error of not found , i can handel it alone as prev but of good message i prefer not 
          if (s.top() == "error") {
            cout <<stackP<< "Error:(illegal " << stackP << ") discard " << inputWords[i]  << endl ; 
            s.pop();
            s.push(stackP) ; 
            i++ ; 
          }else {
            cout << stackP << " to " << table[{ stackP , inputWords[i] }] << endl ; 
          }
          continue ;      
        } 

        // here is  terminal 
      //  stackP.substr( 1 , stackP.size() -1  ) ; // tryig to remove ' ' 

        if (stackP != inputWords[i]) {
             cout<< s.size()<<endl;
             cout <<stackP <<" Error: missing "<< inputWords[i] << ", inserted \n" ;
             continue ; 
        }

        // they are similar 
        cout << "match " << stackP << endl ;
        i++ ; 
    }

    if (s.empty() && i == inputWords.size() ){
        cout << "done" << endl ; 
    }else {
        cout << "not matched input" << endl ; 
    }
    

}

void TableBuilder::print() {
    cout<<endl<<"------table--------"<<endl;
    for (auto t:this->table){
        cout << t.first.first<<" ,"<<t.first.second<<" :";
        cout <<t.second<<endl;
    }
}
