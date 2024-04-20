#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_SIZE 1024L

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
        return true;
    }
    else
    {
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
        return false;
    }
    else
    {
        // hash collision
        if (strcmp(hashtable[index]->name, name) != 0)
        {
            return false;
        }

        // invalid scope
        if (hashtable[index]->scope->scope_level >= scope_level)
        {
            return false;
        }

        struct scope_info *new_scope = (struct scope_info *)malloc(sizeof(struct scope_info));
        new_scope->scope_level = scope_level;
        new_scope->type = (char *)malloc(sizeof(char) * (strlen(type) + 1));
        strcpy(new_scope->type, type);
        new_scope->prev = hashtable[index]->scope;
        hashtable[index]->scope = new_scope;
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
    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("\n\n\n%-50s %10s %4s\n", "Name", "Type", "Level");
        if (hashtable[i])
        {
            char *name = hashtable[i]->name;
            struct scope_info *scope = hashtable[i]->scope;
            while (scope != NULL)
            {
                printf("%-50s %10s %4d\n", name, scope->type, scope->scope_level);
                scope = scope->prev;
            }
        }
    }
}