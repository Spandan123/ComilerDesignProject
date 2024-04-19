#pragma once
#include <bits/stdc++.h>
#include "grammar.h"
#include "parser.h"
#include "../../colors.h"
using namespace std;

int find_char(const char &c, const string &target, int offset = 0)
{
    for (int i = offset; i < target.size(); i++)
    {
        if (target[i] == c)
            return i;
    }
    return -1;
}

class LR1_item_set;

unordered_map<int, unordered_map<string, int>> gotos_table;
unordered_map<int, int> reduce_table;
// 0 -> 1,"fe"

// 0 -> 2, "eine"
unordered_map<int, LR1_item_set *> dfa;
set<int> already_done;
bool duplicate_item(LR1_item_set x);
void print_item_mapping();
class LR1_item_set
{
public:
    unordered_map<string, unordered_map<string, set<string>>> items;
    int num;
    LR1_item_set(unordered_map<string, unordered_map<string, set<string>>> kernel, int num) : items(kernel), num(num)
    {
        // cout << "\n\n";
        while (1)
        {
            unordered_map<string, unordered_map<string, set<string>>> dup_items = items;
            int cnt = 0;
            for (auto k_item : items)
            {
                string n_t = k_item.first;
                // cout << "Non-terminal : " << n_t << endl;
                for (auto prods : k_item.second)
                {
                    string prod_str = prods.first;
                    // cout << "Production : " << prod_str << endl;
                    set<string> follows = prods.second;
                    int dot_pos = find_char('.', prod_str);
                    if (dot_pos == prod_str.size() - 1)
                    {
                                        }
                    int first_gap_after_dot = find_char(' ', prod_str, dot_pos);
                    string next_str = prod_str.substr(dot_pos + 1, first_gap_after_dot - dot_pos - 1);
                    // cout << "Next : " << next_str << endl;
                    if (next_str.empty() || !isNonTerminal(next_str))
                    {
                        continue;
                    }

                    for (auto new_produc : cfg[next_str])
                    {
                        // cout << "New productions : " << new_produc << endl;
                        string new_prod = new_produc;
                        new_prod[0] = '.';
                        for (auto temp : follow[next_str])
                        {
                            if (dup_items[next_str][new_prod].find(temp) == dup_items[next_str][new_prod].end())
                            {
                                dup_items[next_str][new_prod].insert(temp);
                                cnt++;
                            }
                        }
                    }
                }
            }
            if (cnt == 0)
                break;
            else
                items = dup_items;
        }
    }

    bool operator==(const LR1_item_set &rhs) const
    {
        for (auto it : items)
        {
            if (rhs.items.find(it.first) == rhs.items.end())
                return false;

            for (auto it1 : it.second)
            {
                if (rhs.items.at(it.first).find(it1.first) == rhs.items.at(it.first).end())
                    return false;
                if (rhs.items.at(it.first).at(it1.first) != it1.second)
                    return false;
            }
        }
        return true;
    }

    void create_gotos()
    {
        unordered_map<string, unordered_map<string, unordered_map<string, set<string>>>> gotos;
        for (auto elem : items)
        {
            string n_t = elem.first;
            for (auto prods : elem.second)
            {
                string prod_str = prods.first;
                int dot_pos = find_char('.', prod_str);
                int first_gap_after_dot = find_char(' ', prod_str, dot_pos);
                string next_str = prod_str.substr(dot_pos + 1, first_gap_after_dot - dot_pos - 1);
                if (next_str.empty())
                    continue;
                string new_prod = prod_str;
                new_prod[dot_pos] = ' ';
                new_prod[first_gap_after_dot] = '.';
                // cout << new_prod << endl;
                if (first_gap_after_dot == prod_str.size() - 1)
                    gotos[next_str][n_t][new_prod] = prods.second;
                else
                {
                    gotos[next_str][n_t][new_prod] = first[next_str];
                }
            }
        }
        int next_num = dfa.size();
        for (auto goto_ : gotos)
        {
            string next_ = goto_.first;
            unordered_map<string, unordered_map<string, set<string>>> new_kernel;
            for (auto prods : goto_.second)
            {
                string n_t = prods.first;
                for (auto prod : prods.second)
                {
                    string new_prod = prod.first;
                    new_kernel[n_t][new_prod] = prod.second;
                }
            }
            LR1_item_set new_item(new_kernel, next_num);
            if (!duplicate_item(new_item))
            {
                dfa[next_num] = new LR1_item_set(new_kernel, next_num);
                gotos_table[num][next_] = next_num;
                // dfa[next_num]->create_gotos();
                next_num++;
            }
        }
    }

    // sjfe -> .enum id id = id  {follow}

    // n_t = sjfe
    // next_str : enum
    // new_prod : enum.id id = id

public:
    void print_item()
    {
        for (auto it : items)
        {
            for (auto it1 : it.second)
            {
                cout << BLUE << it.first << RESET << " -> " << GREEN << it1.first << RESET << YELLOW << " { " << RESET;
                for (auto it2 : it1.second)
                {
                    cout << WHITE << it2 << RESET << " ";
                }
                cout << YELLOW << "} " << RESET << endl;
            }
            cout << endl;
        }
    }

    static void create_LR1_automaton()
    {
        unordered_map<string, unordered_map<string, set<string>>> kernel;
        // print_cfg();
        kernel["augmented_start"][".program "] = {"$"};
        dfa[0] = new LR1_item_set(kernel, 0);
        // dfa[0]->print_item();
        while (1)
        {
            unordered_map<int, LR1_item_set *> dup_dfa;
            for (auto items : dfa)
            {
                dup_dfa[items.first] = new LR1_item_set(items.second->items, items.first);
            }
            int x = dup_dfa.size();
            // cout << "dfa size : " << x << endl;
            for (auto items : dup_dfa)
            {
                if (already_done.find(items.second->num) == already_done.end())
                {
                    // cout << "Creating gotos for item " << items.second->num << endl;
                    items.second->create_gotos();
                    already_done.insert(items.second->num);
                }
            }
            // cout << "dfa_after size : " << dfa.size() << endl;
            if (x == dfa.size())
            {
                // cout << "Done\n";
                break;
            }
            // print_item_mapping();
        }
        for (auto items : dfa)
        {
            cout << "\n\nItem " << items.first << "\n";
            items.second->print_item();
        }
    }
};

bool duplicate_item(LR1_item_set x)
{
    for (auto it : dfa)
    {
        if (*(it.second) == x)
            return true;
    }
    return false;
}

void print_item_mapping()
{
    for (auto it : gotos_table)
    {
        for (auto temp : it.second)
        {
            cout << it.first << " -> " << temp.first << " : " << temp.second << endl;
        }
    }
}
/*
 "A" -> " E C D.B ", ["a"]
 "B" -> " "  [first("Ba")]
  "A" ->
*/