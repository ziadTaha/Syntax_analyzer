//
// Created by Ahmed on 4/15/2020.
//

#include "FollowMaker.h"

void FollowMaker::make() {

    // for every non-terminal nt: nt->e
    for (auto nt : Productions) {
        set<string> temp;
        Follow.insert({nt.first, temp});
    }

    // add $ to the first one
    set<string> temp;
    temp.insert("$");
    Follow[start] = temp;

    bool test = true;
    while (test) {
        test = false;
        for (auto p  : Productions) {
            set<string> trailer = Follow[p.first];
            for (auto iter = p.second.rbegin();
                 iter != p.second.rend(); iter++) {
                string x = *iter;
                vector<string> tokens = tokenize(*iter);
                for (auto iterr = tokens.rbegin();
                     iterr != tokens.rend(); iterr++) {
                    string xx = *iterr;
                    if (!isTerminal(*iterr) && *iterr != "e") {
                        Follow[*iterr].insert(trailer.begin(), trailer.end());
                        if (First[*iterr].find("e") != First[*iterr].end()) {
                            trailer.insert(First[*iterr].begin(),
                                           First[*iterr].end());
                            trailer.erase("e");
                            trailer.insert("$");
                        } else {
                            trailer = First[*iterr];
                            trailer.erase("e");
                        }
                    } else {
                        trailer = First[*iterr];
                        trailer.erase("e");
                    }
                }
            }
        }
    }
}

FollowMaker::FollowMaker(unordered_map<string, set<string>> productions,
                         unordered_map<string, set<string>> first) {
    Productions = productions;
    First = first;
}

bool FollowMaker::isTerminal(string s) {
    return (s[0] == '\'' && s[s.size() - 1] == '\'' &&
            s.find(' ') == string::npos);
}

unordered_map<string, set<string>> FollowMaker::getFollow() {
    return Follow;
}

void FollowMaker::setStart(string start) {
    FollowMaker::start = start;
}

bool FollowMaker::isNotTerminal(string s) {
    for (auto iter : Productions) {
        if (iter.first == s) return true;
    }
    return false;
}

vector<string> FollowMaker::tokenize(string s) {
    // Vector of string to save tokens
    vector<string> tokens;

    // stringstream class check1
    stringstream check1(s);

    string intermediate;

    // Tokenizing w.r.t. space ' '
    while (getline(check1, intermediate, ' ')) {
        tokens.push_back(intermediate);
    }
    return tokens;
}
