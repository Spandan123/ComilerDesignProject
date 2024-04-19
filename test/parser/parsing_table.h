#pragma once
#include <bits/stdc++.h>
using namespace std;
#include "LR1_automaton.h"

unordered_map<int, unordered_map<string, int>> GOTO;
//<state , <Rpos,terminals>>
//<state , <Spos,terminals>>
unordered_map<int, unordered_map<string, set<string>>> ACTION;

void create_parsing_table()
{
    create_cfg();
    findNonTerminals(cfg);
    LR1_item_set::create_LR1_automaton();

    for (auto it : gotos_table)
    {
        for (auto itt : it.second)
        {
            if (isNonTerminal(itt.first))
            {
                GOTO[it.first][itt.first] = itt.second;
            }
            else
            {
                int pos = itt.second;
                string shift = "S";
                shift += to_string(pos);
                ACTION[it.first][shift].insert(itt.first);
            }
        }
    }

    for (auto it : reduce_table)
    {
        for (auto it1 : (dfa[it.first])->items)
        {
            for (auto prod : it1.second)
            {
                if (prod.first[prod.first.size() - 1] == '.')
                {
                    string new_str = prod.first;
                    new_str[new_str.size() - 1] = ' ';
                    int pos = get_position(it1.first, new_str);
                    string red = "R";
                    red += to_string(pos);
                    ACTION[dfa[it.first]->num][red] = prod.second;
                }
            }
        }
    }
}

void print_parsing_table()
{
    cout << "\n\n      ";
    //
    for (auto it : ACTION)
    {
        for (auto itt : it.second)
        {
            for (auto ter : itt.second)
            {
                cout << it.first << "  " << ter << " " << itt.first << "\n";
            }
        }
    }

    for (auto it : GOTO)
    {
        for (auto itt : it.second)
        {
            cout << it.first << "  " << itt.first << "  " << itt.second << "\n";
        }
    }
    // cout << terminals.size();
}

// A -> b.c

// A -> b.C