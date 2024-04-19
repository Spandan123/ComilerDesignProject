#include <bits/stdc++.h>
#include <string.h>
#include "grammar.h"
#include "LR1_automaton.h"
#include "../lexer/lexer.h"
//  #include <D:\compiler design project\ComilerDesignProject\src\lexer\lexeme.h>

using namespace std;

vector<string> nonterminals;
vector<string> terminals = {};
vector<string> special_charactershere = {};
unordered_map<string, set<string>> first;
unordered_map<string, set<string>> follow;
string start_symbol = "program";
unordered_map<std::string, std::vector<std::string>> augmented_gramamr;
unordered_map<string, vector<pair<string, set<string>>>> actionTable;
unordered_map<string, vector<pair<string, set<string>>>> gotoTable;

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

vector<string> findNonTerminals(unordered_map<std::string, std::vector<std::string>> cfg)
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

bool isNonTerminal(string s)
{
    if (find(nonterminals.begin(), nonterminals.end(), s) != nonterminals.end())
        return 1;
    return 0;
}

void findTerminals(unordered_map<std::string, std::vector<std::string>> cfg)
{
    for (auto it : cfg)
    {
        string a = it.first;
        for (auto prod : it.second)
        {
            prod = trim(prod);
            vector<string> rhs = split(prod, ' ');
            for (auto it1 : rhs)
            {
                if (find(nonterminals.begin(), nonterminals.end(), (it1)) == nonterminals.end())
                {
                    if (find(terminals.begin(), terminals.end(), (it1)) == terminals.end())
                    {
                        terminals.push_back((it1));
                        first[it1].insert(it1);
                    }
                }
            }
        }
    }
}

void find_first(unordered_map<std::string, std::vector<std::string>> cfg)
{
    for (auto it = cfg.begin(); it != cfg.end(); it++)
    {
        string a = it->first;
        for (auto &prod : it->second)
        {
            prod = trim(prod);
            vector<string> rhs = split(prod, ' ');
            for (auto it1 = rhs.begin(); it1 != rhs.end(); it1++)
            {
                //     cout << *(it1) << "  a  ";
                if (!isNonTerminal(*(it1)))
                {
                    first[a].insert(*(it1));
                    if (find(terminals.begin(), terminals.end(), *(it1)) == terminals.end())
                        terminals.push_back(*(it1));
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

void initialise_follow(unordered_map<std::string, std::vector<std::string>> cfg)
{
    for (auto it : cfg)
    {
        follow[it.first] = {};
    }
    follow[start_symbol].insert("$");
    terminals.push_back("$");
}

void find_follow(unordered_map<std::string, std::vector<std::string>> cfg)
{
    for (auto it : cfg)
    {
        string a = it.first;
        for (auto prod : it.second)
        {
            prod = trim(prod);
            vector<string> rhs = split(prod, ' ');
            int size = rhs.size();
            if (size == 1)
            {
                // cout << rhs[0] << endl;
                if (!isNonTerminal(rhs[0]))
                {
                    continue;
                }
                else
                {
                    for (auto x = follow[a].begin(); x != follow[a].end(); x++)
                    {
                        follow[rhs[0]].insert(*(x));
                    }
                }
            }
            else
            {
                for (int i = size - 1; i > -1; i--)
                {
                    if (!isNonTerminal(rhs[i]))
                    {
                        continue;
                    }
                    else
                    {
                        if (i == size - 1)
                        {
                            for (auto x = follow[a].begin(); x != follow[a].end(); x++)
                            {
                                follow[rhs[i]].insert(*(x));
                            }
                        }
                        else
                        {
                            for (auto y : first[rhs[i + 1]])
                            {
                                follow[rhs[i]].insert(y);
                            }
                        }
                    }
                }
            }
        }
    }
}

void augmentedGrammar()
{
    augmented_gramamr["augmented_start"] = {"program"};
    for (auto it : cfg)
    {
        augmented_gramamr[it.first] = it.second;
    }
}

void LR1ParsingTable()
{
}

void run_parser()
{
    // unordered_map<std::string, std::vector<std::string>> cfg_here = create_cfg();
    create_cfg();
    // print_cfg();
    nonterminals = findNonTerminals(cfg);
    // printMap(nonterminals);
    findTerminals(cfg);
    initialize_first();
    // printMap(first);
    find_first(cfg);
    find_first(cfg);
    initialise_follow(cfg);
    find_follow(cfg);
    find_follow(cfg);
    // printMap(first);
    printMap(follow);
    //    printMap(nonterminals);
    //    cout << nonterminals.size();
    // printMap(terminals);
}

int main(int argc, char *argv[])
{
    run_parser();
    remove(argv[0]);
}
