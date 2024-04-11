#include <bits/stdc++.h>

using namespace std;
#define _INCR_NUM(x) x++;
static int Item_number = 0;

class LR1_item
{
public:
    int num;
    unordered_map<string, pair<string, string>> productions;
    unordered_map<string, int> GOTO;

    LR1_item(unordered_map<string, pair<string, string>> productions) : num(Item_number), productions(productions)
    {
        while (1)
        {
            bool added = false;
            for (auto production : productions)
            {
                int i = 0;
                for (; production.second.first[i] != '.' && production.second.first[i] != '\0'; i++)
                {
                }
                int j = i;
                for (; production.second.first[j] != ' ' && production.second.first[j] != '\0'; j++)
                {
                }
                string goto_ = production.second.first.substr(i + 1, max(j - i - 1, 0));
                if (GOTO.find(goto_) != GOTO.end() && goto_ != "")
                {
                    _INCR_NUM(Item_number);
                    added = true;
                    GOTO[goto_] = Item_number;
                    unordered_map<string, pair<string, string>> new_productions = productions;
                }
            }
            if (!added)
                break;
        }
    }
};