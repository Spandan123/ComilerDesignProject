#pragma once
#include <bits/stdc++.h>
using namespace std;
#include "LR1_automaton.h"

unordered_map<int, unordered_map<string, int>> GOTO;
unordered_map<int, unordered_map<string, string>> ACTION;

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
                string action;
            }
        }
    }
}

// A -> b.c

// A -> b.C