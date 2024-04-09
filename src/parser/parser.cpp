#include <bits/stdc++.h>
#include <string.h>
#include "grammar.h"
#include <D:\compiler design project\ComilerDesignProject\src\lexer\lexer.h>
//  #include <D:\compiler design project\ComilerDesignProject\src\lexer\lexeme.h>

using namespace std;

vector<string> nonterminals;
vector<string> terminals = {"keyword", "constant", "identifier", "special_character", "operator"};
unordered_map<string, vector<string>> first;
unordered_map<string, vector<string>> follow;

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

vector<string> findNonTerminals(vector<string> &terminals, unordered_map<std::string, std::vector<std::string>> cfg)
{
    for (auto it = cfg.begin(); it != cfg.end(); it++)
    {
        terminals.push_back(it->first);
    }
    return terminals;
}

void initialize_first()
{
    for (auto nont : nonterminals)
    {
        first[nont] = {};
    }
    for (auto ter : terminals)
    {
        first[ter].push_back(ter);
    }
}

void find_first()
{
}

void find_follow() {}

int main(int argc, char *argv[])
{
    unordered_map<std::string, std::vector<std::string>> cfg_here = create_cfg();
    print_cfg();
    terminals = findNonTerminals(terminals, cfg_here);
    printMap(terminals);
    remove(argv[0]);
}
