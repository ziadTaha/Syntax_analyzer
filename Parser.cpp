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
