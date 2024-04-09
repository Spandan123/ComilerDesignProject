#include <bits/stdc++.h>
#include <string.h>
#include "grammar.h"
#include <D:\compiler design project\ComilerDesignProject\src\lexer\lexer.h>
//  #include <D:\compiler design project\ComilerDesignProject\src\lexer\lexeme.h>

using namespace std;

vector<string> nonterminals;
vector<string> terminals = {"keyword", "constant", "identifier", "special_character", "operator"};
vector<string> special_charactershere = {};
unordered_map<string, set<string>> first;
unordered_map<string, set<string>> follow;

string trim(const string &s)
{
    size_t first = s.find_first_not_of(" \t\n\r");
    if (first == string::npos)
    {
        return "";
    }
    size_t last = s.find_last_not_of(" \t\n\r");
    if (last == string::npos)
    {
        return "";
    }
    return s.substr(first, last - first + 1);
}

vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(trim(token));
    }
    return tokens;
}

void printMap(vector<string> x)
{
    for (auto it = x.begin(); it != x.end(); it++)
    {
        cout << *(it) << " ";
    }
    cout << endl;
}

void printMap(unordered_map<string, set<string>> x)
{
    cout << endl;
    int i = 0;
    for (auto it = x.begin(); it != x.end(); it++)
    {
        cout << it->first << " " << i << " -> {";
        i++;
        for (auto &prod : it->second)
        {
            cout << prod << " ";
        }
        cout << "}\n";
    }
}

vector<string> findNonTerminals(vector<string> &terminals, unordered_map<std::string, std::vector<std::string>> cfg)
{
    for (auto it = cfg.begin(); it != cfg.end(); it++)
    {
        nonterminals.push_back(it->first);
    }
    return nonterminals;
}

void initialize_first()
{
    vector<string> sp = {"{", "}"};
    for (auto nont : nonterminals)
    {
        first[nont] = {};
    }
    for (auto ter : terminals)
    {
        first[ter].insert(ter);
    }
    for (int i = 0; i < sp.size(); i++)
    {
        first[sp[i]].insert(sp[i]);
    }
}

bool isTerminal(string s)
{
    if (find(terminals.begin(), terminals.end(), s) != terminals.end())
        return 1;
    return 0;
}

void find_first(unordered_map<std::string, std::vector<std::string>> cfg)
{
    for (auto it = cfg.begin(); it != cfg.end(); it++)
    {
        string a = it->first;
        for (auto &prod : it->second)
        {
            vector<string> rhs = split(prod, ' ');
            for (auto it1 = rhs.begin(); it1 != rhs.end(); it1++)
            {
                //     cout << *(it1) << "  a  ";
                if (isTerminal(*(it1)))
                {
                    first[a].insert(*(it1));
                    break;
                }
                else if (*(it1) == "for")
                {
                    first[a].insert("keyword");
                    break;
                }
                else
                {
                    string s = *(it1);
                    for (auto it2 = first[s].begin(); it2 != first[s].end(); it2++)
                    {
                        first[a].insert(*(it2));
                    }
                    break;
                }
            }
            // cout << endl;
        }
    }
}

void find_follow() {}

int main(int argc, char *argv[])
{
    unordered_map<std::string, std::vector<std::string>> cfg_here = create_cfg();
    print_cfg();
    nonterminals = findNonTerminals(terminals, cfg_here);
    printMap(nonterminals);
    initialize_first();
    printMap(first);
    find_first(cfg_here);
    find_first(cfg_here);
    printMap(first);
    remove(argv[0]);
}
