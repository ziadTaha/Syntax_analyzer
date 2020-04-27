//
// Created by zeny on 4/15/20.
//

#include "TableBuilder.h"

#include <utility>

TableBuilder::TableBuilder(unordered_map<string, set<string>> first, unordered_map<string, set<string>> follow,
                           unordered_map<string, set<string>> productions)
    : first(first), follow(follow), productions(productions)
{

    calcTerminals();
}

void TableBuilder::build()
{
    map<pair<string, string>, string> t = {};
    for (auto production : this->productions)
    {
        for (auto terminal : this->terminals)
        {
            t[{production.first, terminal}] = "error";
        }
        for (auto product : production.second)
        {
            for (auto terminal : this->terminals)
            {
                bool thisSlotIsTaken = false;
                if (this->first[product].find(terminal) != this->first[product].end())
                {
                    t[{production.first, terminal}] = product;
                    thisSlotIsTaken = true;
                }
                if (this->follow[production.first].find(terminal) != this->follow[production.first].end())
                { //se if it can be [product]
                    if (this->first[production.first].find("eeee") != this->first[production.first].end())
                    {
                        if (this->productions[production.first].find("eeee") != this->productions[production.first].end() &&
                            thisSlotIsTaken)
                        {
                            errorMes.push_back("multiple productions in one slot error !!");
                            break;
                        }
                        t[{production.first, terminal}] = "eeee";
                    }
                    else if (t[{production.first, terminal}] == "error")
                    {
                        t[{production.first, terminal}] = "synch";
                    }
                }
            }
        }
    }
    this->table = t;
}

void TableBuilder::calcTerminals()
{
    set<string> s;
    for (const auto &production : this->productions)
    {
        for (const auto &product : production.second)
        {
            vector<string> words = tokenize(product);
            for (const auto &word : words)
            {
                if (isTerminal(word))
                {
                    s.insert(word);
                }
            }
        }
    }
    s.insert("\'$\'");
    this->terminals = s;
}

vector<string> TableBuilder::tokenize(string s)
{
    // Vector of string to save tokens
    vector<string> tokens;

    // stringstream class check1
    stringstream check1(s);

    string intermediate;
    // Tokenizing w.r.t. space ' '
    while (getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

bool TableBuilder::isTerminal(string s)
{
    return (s[0] == '\'' && s[s.size() - 1] == '\'' && s.find(' ') == string::npos);
}
/*
bool TableBuilder::isTerminal(string s) {
    return (s[0]=='\''&&s[s.size()-1]=='\''&&s.find(' ')==string::npos);
}
*/
void TableBuilder::lastInput(string firstNon)
{

    vector<string> inputWords;

    // reading input
    fstream file;
    string word, t, q, filename;
    filename = "outputForPhase1.txt";
    file.open(filename.c_str());

    while (file >> word)
    {
        word = "\'" + word + "\'";
        inputWords.push_back(word);
    }

    // ----------
    stack<string> s;
    s.push("\'$\'");
    s.push(firstNon);
    inputWords.push_back("\'$\'");
    int i = 0;
    if (!errorMes.size())
    {
        while (!s.empty() && i < inputWords.size())
        {
            string stackP = s.top();
            s.pop();
            //  cout << "ssss "  << stackP << " " << i << " " << inputWords[i] << endl ;
            if (stackP == "synch")
            {
                stack<string> temp = s;
                vector<string> temp2;
                string my_stack = "";
                while (!temp.empty())
                {
                    temp2.push_back(temp.top());
                    temp.pop();
                }
                for (int k = temp2.size() - 1; k >= 0; k--)
                    my_stack += temp2[k] + " ";
                my_stack += stackP + "\n";
                errorMes.push_back(my_stack);
                string my_input = "";
                for (int k = inputWords.size() - 1; k >= i; k--)
                    my_input += inputWords[k] + " ";
                my_input += "\n";
                errorMes.push_back(my_input);

                errorMes.push_back("error synch\n");
                // cout << "error synch \n" ;
                continue;
            }

            if (stackP == "eeee")
            {
                continue;
            }

            if (!isTerminal(stackP))
            {
                // may the string from table must spilt
                 stack<string> temp = s;
                    vector<string> temp2;
                    string my_stack = "";
                    while (!temp.empty())
                    {
                        temp2.push_back(temp.top());
                        temp.pop();
                    }
                    for (int k = temp2.size() - 1; k >= 0; k--)
                        my_stack += temp2[k] + " ";
                    my_stack += stackP + "\n";
                    errorMes.push_back(my_stack);
                    string my_input = "";
                    for (int k = inputWords.size() - 1; k >= i; k--)
                        my_input += inputWords[k] + " ";
                    my_input += "\n";
                    errorMes.push_back(my_input);

                if (table[{stackP, inputWords[i]}] != "")
                {
                    vector<string> ss = tokenize(table[{stackP, inputWords[i]}]);
                    for (int j = ss.size() - 1; j >= 0; j--)
                    {
                        if (ss[j] != " " && ss[j] != "")
                            s.push(ss[j]);
                    }
                }
                else
                {
/*                    stack<string> temp = s;
                    vector<string> temp2;
                    string my_stack = "";
                    while (!temp.empty())
                    {
                        temp2.push_back(temp.top());
                        temp.pop();
                    }
                    for (int k = temp2.size() - 1; k >= 0; k--)
                        my_stack += temp2[k] + " ";
                    my_stack += stackP + "\n";
                    errorMes.push_back(my_stack);
                    string my_input = "";
                    for (int k = inputWords.size() - 1; k >= i; k--)
                        my_input += inputWords[k] + " ";
                    my_input += "\n";
                    errorMes.push_back(my_input);
*/
                    errorMes.push_back("error in table\n");
                    errorMes.push_back(stackP + " " + inputWords[i]);
                    break;
                    //cout << "error in table\n"  ;
                    //cout << "Www " << stackP << " ff " << inputWords[i] << endl ;
                    //continue ;
                }

                // handel error of not found , i can handel it alone as prev but of good message i prefer not
                if (s.top() == "error")
                {
                    stack<string> temp = s;
                    vector<string> temp2;
                    string my_stack = "";
                    while (!temp.empty())
                    {
                        temp2.push_back(temp.top());
                        temp.pop();
                    }
                    for (int k = temp2.size() - 1; k >= 0; k--)
                        my_stack += temp2[k] + " ";
                    my_stack += stackP + "\n";
                    errorMes.push_back(my_stack);
                    string my_input = "";
                    for (int k = inputWords.size() - 1; k >= i; k--)
                        my_input += inputWords[k] + " ";
                    my_input += "\n";
                    errorMes.push_back(my_input);

                    errorMes.push_back(stackP + "Error:(illegal " + stackP + ") discard " + inputWords[i] + "\n");
                    //cout <<stackP<< "Error:(illegal " << stackP << ") discard " << inputWords[i]  << endl ;
                    s.pop();
                    s.push(stackP);
                    i++;
                }
                else
                {
                   
                    errorMes.push_back(stackP + " to " + table[{stackP, inputWords[i]}] + "\n");
                    // cout << stackP << " to " << table[{ stackP , inputWords[i] }] << endl ;
                }
                continue;
            }

            // here is  terminal
            //  stackP.substr( 1 , stackP.size() -1  ) ; // tryig to remove ' '

            if (stackP != inputWords[i])
            {
                //  cout<< s.size()<<endl;
                stack<string> temp = s;
                vector<string> temp2;
                string my_stack = "";
                while (!temp.empty())
                {
                    temp2.push_back(temp.top());
                    temp.pop();
                }
                for (int k = temp2.size() - 1; k >= 0; k--)
                    my_stack += temp2[k] + " ";
                my_stack += stackP + "\n";
                errorMes.push_back(my_stack);
                string my_input = "";
                for (int k = inputWords.size() - 1; k >= i; k--)
                    my_input += inputWords[k] + " ";
                my_input += "\n";
                errorMes.push_back(my_input);

                errorMes.push_back(stackP + " Error: missing " + inputWords[i] + ", inserted \n");
                // cout <<stackP <<" Error: missing "<< inputWords[i] << ", inserted \n" ;
                continue;
            }

            // they are similar
            stack<string> temp = s;
            vector<string> temp2;
            string my_stack = "";
            while (!temp.empty())
            {
                temp2.push_back(temp.top());
                temp.pop();
            }
            for (int k = temp2.size() - 1; k >= 0; k--)
                my_stack += temp2[k] + " ";
            my_stack += stackP + "\n";
            errorMes.push_back(my_stack);
            string my_input = "";
            for (int k = inputWords.size() - 1; k >= i; k--)
                my_input += inputWords[k] + " ";
            my_input += "\n";
            errorMes.push_back(my_input);

            errorMes.push_back("match " + stackP + "\n");
            //cout << "match " << stackP << endl ;
            i++;
        }

        if (s.empty() && i == inputWords.size())
        {
            errorMes.push_back("done\n");
            // cout << "done" << endl ;
        }
        else
        {
            errorMes.push_back("not matched input\n");
            // cout << "not matched input" << endl ;
        }
    }

    ofstream MyFile("outputForphase2.txt");
    int c = 0 ; 

    for (string s : errorMes)
    {
        MyFile << s;

        c++ ; 
         
        if ( c % 3 == 0  )
            MyFile << "-------------------" << endl ;  

       
    }
    // Close the file
    MyFile.close();
}

void TableBuilder::print()
{
    cout << endl
         << "------table--------" << endl;
    for (auto t : this->table)
    {
        cout << t.first.first << " ," << t.first.second << " :";
        cout << t.second << endl;
    }
}
