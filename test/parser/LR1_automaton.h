#include <bits/stdc++.h>
#include "grammar.h"
#include "parser.h"

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

unordered_map<int, LR1_item_set *> LR1_automaton_map;
unordered_map<int, pair<int, string>> gotos;

class LR1_item_set
{
private:
    unordered_map<string, unordered_map<string, set<string>>> items;

    LR1_item_set(unordered_map<string, unordered_map<string, set<string>>> kernel) : items(kernel)
    {
        while (1)
        {
            int cnt = 0;
            unordered_map<string, unordered_map<string, set<string>>> dup_item = items;
            for (auto p : items)
            {
                string A = p.first;
                for (auto pp : p.second)
                {
                    string prod = pp.first;
                    int n = find_char('.', prod);
                    if (n != prod.size() - 1)
                    {
                        int x = find_char(' ', prod, n);
                        int y = find_char(' ', prod, x);
                        string B = prod.substr(n + 1, x - n - 1);
                        string beta = x == prod.size() - 1 ? "" : prod.substr(x + 1, y - x - 1);
                        if (cfg.find(B) == cfg.end())
                        {
                            continue;
                        }
                        for (auto new_prods : cfg[B])
                        {
                            string ppp = new_prods;
                            ppp[0] = '.';
                            if (beta == "")
                            {
                                for (auto f : pp.second)
                                {
                                    if (items.find(B) != items.end() && items[B].find(ppp) != items[B].end() && items[B][ppp].find(f) == items[B][ppp].end())
                                    {
                                        dup_item[B][ppp].insert(f);
                                        cnt++;
                                    }
                                }
                                continue;
                            }
                            for (auto f : first[beta])
                            {
                                if (items.find(B) != items.end() && items[B].find(ppp) != items[B].end() && items[B][ppp].find(f) == items[B][ppp].end())
                                {
                                    dup_item[B][ppp].insert(f);
                                    cnt++;
                                }
                            }
                        }
                    }
                }
            }
            if (!cnt)
                break;
            else
                items = dup_item;
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
        unordered_map<string, LR1_item_set> temp;
        for (auto item : items)
        {
            string A = item.first;
            for (auto pp : item.second)
            {
                string prod = pp.first;
                int n = find_char('.', prod);
                if (n != prod.size() - 1)
                {
                    string B = prod.substr(n + 1);
                }
            }
        }
    }

public:
    void print_item()
    {
        for (auto it : items)
        {
            cout << it.first << endl;
            for (auto it1 : it.second)
            {
                cout << it1.first << " -> ";
                for (auto it2 : it1.second)
                {
                    cout << it2 << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    friend void create_LR1_automaton()
    {
        unordered_map<string, unordered_map<string, set<string>>> kernel;
        kernel[" program_ "][".program "] = {"$"};
        LR1_automaton_map[0] = new LR1_item_set(kernel);
        LR1_automaton_map[0]->print_item();
    }
};

/*
 "A" -> " E C D.B ", ["a"]
 "B" -> " "  [first("Ba")]
  "A" ->
*/