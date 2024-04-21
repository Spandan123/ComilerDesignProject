#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 1024L

int NUM = 0;

void print_symbol_table();

struct scope_info
{
public:
    int scope_level;
    char *type;
    struct scope_info *prev;
};

struct entry
{
public:
    char *name;
    struct scope_info *scope;
};

long hash_(char *name)
{
    long ans = 0;
    for (int i = 0; name[i] != '\0'; i++)
    {
        ans += name[i] * i;
    }
    return ans % MAX_SIZE;
}

struct entry *hashtable[MAX_SIZE] = {NULL};

bool create_entry(char *name)
{
    long index = hash_(name);
    if (hashtable[index] == NULL)
    {
        hashtable[index] = (struct entry *)malloc(sizeof(struct entry));
        hashtable[index]->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(hashtable[index]->name, name);
        hashtable[index]->scope = NULL;
        print_symbol_table();
        NUM++;
        return true;
    }
    else
    {
        cout << "id already exists";
        return false;
    }
}

// 0   |  |   id + id
// 0 5 |id|   + id
// 0   |F|   + id
// 0 3 |F|   +
//

bool insert(char *name, char *type, int scope_level)
{
    long index = hash_(name);
    if (hashtable[index] == NULL)
    {
        cout << "id already exists\n";
        return false;
    }
    else
    {
        // hash collision
        if (strcmp(hashtable[index]->name, name) != 0)
        {
            cout << "invalid hashvalue\n";
            return false;
        }

        // invalid scope
        if (hashtable[index]->scope->scope_level >= scope_level)
        {
            cout << "invalid scope\n";
            return false;
        }

        struct scope_info *new_scope = (struct scope_info *)malloc(sizeof(struct scope_info));
        new_scope->scope_level = scope_level;
        new_scope->type = (char *)malloc(sizeof(char) * (strlen(type) + 1));
        strcpy(new_scope->type, type);
        new_scope->prev = hashtable[index]->scope;
        hashtable[index]->scope = new_scope;
        cout << "inserting id : " << name;
        print_symbol_table();
        return true;
    }
}

bool remove(char *name, int scope_level)
{
    long index = hash_(name);
    if (hashtable[index] == NULL || strcmp(hashtable[index]->name, name) != 0 || hashtable[index]->scope->scope_level != scope_level)
    {
        return false;
    }
    else
    {
        if (hashtable[index]->scope->prev == NULL)
        {
            struct entry *temp = hashtable[index];
            hashtable[index] = NULL;
            free(temp);
        }
        else
        {
            struct scope_info *temp = hashtable[index]->scope;
            hashtable[index]->scope = hashtable[index]->scope->prev;
            free(temp);
        }
        return true;
    }
}

void print_symbol_table()
{
    if(NUM==0) return;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("\n\n\n%-10s %10s %4s\n", "Name", "Type", "Level");
        if (hashtable[i])
        {
            char *name = hashtable[i]->name;
            struct scope_info *tempscope = hashtable[i]->scope;
            while (tempscope != NULL)
            {
                printf("%-10s %10s %4d\n", name, tempscope->type, tempscope->scope_level);
                tempscope = tempscope->prev;
            }
        }
    }
}