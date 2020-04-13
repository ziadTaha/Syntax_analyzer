#include "Parser.h"

Parser::Parser(/* args */)
{
}

Parser::~Parser()
{
}

void Parser::readGrammer(string path)
{
}

vector<string> Parser::stringToVector(string s)
{
   std::stringstream ss(s);
   std::istream_iterator<std::string> begin(ss);
   std::istream_iterator<std::string> end;
   std::vector<std::string> vstrings(begin, end);
  //std::copy(vstrings.begin(), vstrings.end());
   return vstrings;
}
string Parser::vectorToString(vector<string > vec)
{
    std::ostringstream vts;
    if(!vec.empty())
    {
       std::copy(vec.begin(), vec.end()-1, 
        std::ostream_iterator<int>(vts, " ")); 
    } 
    return vts.str();
}
void Parser::immediateLeftRecursion(string a,vector <string> ex)
{
 std::vector<std::string> aString;
 std::vector<std::string> bString;
 string a_=a;
 a_.push_back('\'');
 for(string s:ex)
 {
    std::vector<std::string> temp =stringToVector(s);
    string sbegin =*temp.begin();
    if(a==sbegin)
    {
       temp.erase(temp.begin());
       temp.push_back(a_);
       string tempString =vectorToString(temp);
       bString.push_back(tempString);
    }
    else
    {
       temp.push_back(a_);
       string tempString =vectorToString(temp);
       aString.push_back(tempString);
    }

 }
 if(!bString.empty())
 {
    string e="";
    bString.push_back(e);
    nonTerminal[a]=aString;
    nonTerminal[a_]=bString;
    
 }
}
void Parser::replaceAwithB(string a,string b)
{
    std::vector<std::string> aString=nonTerminal[a];
    std::vector<std::string> bString=nonTerminal[b];
    std::vector<std::string> pre;
    std::vector<std::string> result;
    for(string s: aString)
    {
       std::vector<std::string> temp =stringToVector(s);
       string sbegin =*temp.begin();
       if(sbegin==b)
       {
         temp.erase(temp.begin());
         string tempString =vectorToString(temp);
         pre.push_back(tempString);
       }
       else
       {
          result.push_back(s);
       }   
    }
    for(string s : pre)
    {
       for(string sb : bString)
       {
          std::vector<std::string> temp =stringToVector(sb);
          temp.push_back(s);
          string tempString =vectorToString(temp);
          result.push_back(tempString);
       }
    }
    if(!pre.empty())
    {
       nonTerminal[a]=result;
    }
}
void Parser::leftRecursion()
{
    unordered_map <string , vector <string> >::iterator itrI;
    unordered_map <string , vector <string> >::iterator itrJ;
    for(itrI=nonTerminal.begin();itrI!=nonTerminal.end();++itrI)
    {
       string a=itrI->first;
       for(itrJ=nonTerminal.begin();itrJ!=itrI;++itrJ)
       {
          string b=itrJ->first;
          replaceAwithB(a,b);
       }

       immediateLeftRecursion(a,nonTerminal[a]);
    }
     
}
void Parser::leftFactoring()
{
   for (auto a : nonTerminal)
   {

      vector<string> v = a.second;

      sort(v.begin(), v.end());

      for ( string g : v ) 
         cout << g << endl ; 

      for (int i = 0; i < v.size(); i++)
      {

         int j = i +1 ;

         vector<string> s = stringToVector(v[i]);

         while (j < v.size())
         {
             
            vector<string> spliting = stringToVector(v[j]);
            if (spliting[0] == s[0]){
               
               j++;
            }
            else
            {
               break;
            }
           
         }

         if (j == i + 1)
            continue;

         cout << i << " " << j -1  << " "  << 0 << endl ; 
          

         int counter = 1;
         int indexOfebslon = -1;
         bool endOfloop = true;

         while (endOfloop)
         {
            int start;
            for (start = i + 1; start < j; start++)
            {
               if (counter < s.size())
               {
                  vector<string> ss = stringToVector(v[start]);
                  if (counter >= ss.size()) // will make problem 
                     break;
                  if (s[counter] != ss[counter])
                     break;

                  /*cout << s[counter] << " "  << i <<  " "  << start  <<  " " << ss[counter] << endl ;
                  cout << v[i] << endl ; 
                  cout << v[start] << endl ;  */
               }
            }
            if (start == j) {
               counter++ ; 
            } 
            break ; 
         }

         counter-- ; 

         cout << i << " " << j -1  << " "  << counter << endl ; 

         i = j - 1;
      }
   }



}
