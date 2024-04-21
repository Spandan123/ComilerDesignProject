#pragma once
#include <bits/stdc++.h>
using namespace std;
#include "LR1_automaton.h"
#include "grammar.h"
#include "../symbol-table/symbolTable.h"

unordered_map<int, unordered_map<string, int>> GOTO;
//<state , <Rpos,terminals>>
//<state , <Spos,terminals>>
unordered_map<int, unordered_map<string, string>> ACTION;

template <typename T>
void print_stack(stack<T> s)
{
    T a;
    cout << "\n";
    while (!s.empty())
    {
        a = s.top();
        s.pop();
        cout << a << " ";
    }
    cout << "\n";
}

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
                ACTION[it.first][itt.first] = "S" + to_string(itt.second);
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
                    // ACTION[dfa[it.first]->num]["R" + to_string(pos)] = prod.second
                    for (auto it2 : prod.second)
                    {
                        ACTION[dfa[it.first]->num][it2] = "R" + to_string(pos);
                    }
                }
            }
        }
    }
}

void print_parsing_table()
{
    cout << "\n\n";
    //
    for (auto it : ACTION)
    {
        for (auto itt : it.second)
        {
            cout << it.first << "  " << itt.first << "  " << itt.second << "\n";
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

bool parse(char *input)
{
    int curr_scope = 0;
    string str_input = string(input);
    stack<string> st;
    stack<int> states;
    states.push(0);
    string last_type = "";
    bool function_pararm = false;
    bool loop_param = false;
    cout << "\n\n============== PARSING =================\n\n";
    int offset = 0;
    while (offset < str_input.size())
    {
        int n = find_char(' ', str_input, offset);
        string top = str_input.substr(offset, n - offset);
        offset = n + 1;
        cout << "TOP : " << top << endl;
        if (curr_scope < 0)
        {
            return false;
        }
        if (top == "{")
        {
            curr_scope++;
        }
        if (top == "}")
        {
            remove((char *)top.c_str(), curr_scope);
            //print_symbol_table();
            curr_scope--;
            if (function_pararm)
            {
                function_pararm = false;
                remove((char *)top.c_str(), curr_scope);
                //print_symbol_table();
                curr_scope--;
            }
            if (loop_param)
            {
                loop_param = false;
                remove((char *)top.c_str(), curr_scope);
                //print_symbol_table();
                curr_scope--;
            }
            if (curr_scope < 0)
            {
                return false;
            }
        }
        if (top == "(")
        {
            if (st.empty())
            {
                return false;
            }
            else if (st.top() == "id")
            {
                function_pararm = true;
                curr_scope++;
            }
            else if (st.top() == "for")
            {
                loop_param = true;
                curr_scope++;
            }
        }
        // if (st.empty())
        // {
        //     cout << "Empty stack!\n";
        //     st.push(top);
        //     continue;
        // }
        if (top == "id")
        {
            create_entry((char *)top.c_str());
            //print_symbol_table();
            if (!st.empty() && st.top() == "basic_type")
            {
                // give id name
                if (!insert((char *)top.c_str(), (char *)last_type.c_str(), curr_scope))
                {
                    return false;
                }
            }
        }
        //     if (isNonTerminal(top))
        //     {
        //         cout << "Found non terminal : " << top << "\n";
        //         if (GOTO.find(states.top()) == GOTO.end() && GOTO[states.top()].find(string(top)) == GOTO[states.top()].end())
        //         {
        //             cout << "Invalid input!\n";
        //             return false;
        //         }
        //         states.push(GOTO[states.top()][top]);
        //         st.push(top);
        //     }
        //     else
        //     {
        //         cout << "Found terminal : " << top << "\n";
        //         if (ACTION.find(states.top()) == ACTION.end() && ACTION[states.top()].find(string(top)) == ACTION[states.top()].end())
        //         {
        //             cout << "Invalid input!\n";
        //             return false;
        //         }
        //         char action = ACTION[states.top()][top][0];
        //         if (action == 'R')
        //         {
        //             cout << "Action : reduce \n";
        //             int rule_num = stoi(ACTION[states.top()][string(top)].substr(1));
        //             string lhs = get_prod(rule_num).first;
        //             string rhs = get_prod(rule_num).second;
        //             vector<string> rhs_vec = split(rhs, ' ');
        //             for (int i = rhs_vec.size() - 1; i >= 0; i--)
        //             {
        //                 string temp = st.top();
        //                 if (temp != rhs_vec[i])
        //                     return false;
        //                 st.pop();
        //                 if (!states.empty())
        //                     states.pop();
        //                 else
        //                     return false;
        //             }
        //             st.push(lhs);
        //             states.push(GOTO[states.top()][st.top()]);
        //         }
        //         else
        //         {
        //             cout << "Action : shift \n";
        //             cout << "input Stack before shift : ";
        //             print_stack(st);
        //             st.push(top);
        //             cout << "input stack after shift : ";
        //             print_stack(st);
        //             string act = ACTION[states.top()][st.top()];
        //             if (act == "")
        //             {
        //                 cout << "Invalid\n";
        //                 return false;
        //             }
        //             cout << "action : " << ACTION[states.top()][st.top()] << endl;
        //             cout << "states before shift : ";
        //             print_stack(states);
        //             states.push(stoi(ACTION[states.top()][st.top()].substr(1)));
        //             cout << "states after shift : ";
        //             print_stack(states);
        //         }
        //     }
        //     cout << "TOP : " << top << endl;
        // }
        // if (!st.empty() && st.top() == "augmented_start")
        // {
        //     print_symbol_table();
        //     return true;
        // }
        // else
        //     return false;
    }
    return true;
}