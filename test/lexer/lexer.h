//
// Created by aviroop on 4/4/24.
//
#pragma once
#ifndef FINAL_ASSIGNMENT_LEXER_H
#define FINAL_ASSIGNMENT_LEXER_H
#endif // FINAL_ASSIGNMENT_LEXER_H

#include <stdlib.h>
#include <string.h>
#include "../symbol-table/symbolTable.h"
struct token
{
    char *value;
    char *type;
    int valid;
    int len;
};

struct token_list
{
    int max_capacity;
    struct token *list;
};

char *keywords[] = {
    "auto", "double", "int", "struct",
    "break", "else", "long", "switch",
    "case", "enum", "register", "typedef",
    "char", "extern", "return", "union",
    "const", "float", "short", "unsigned",
    "continue", "for", "signed", "void",
    "default", "goto", "sizeof", "volatile",
    "do", "if", "static", "while"};

char special_characters[] = {
    '{', '}', '(', ')',
    '{', '}', ',', ':',
    ';', '*', '#',
    '.', '~'};

char *operators[] = {
    "+", "-", "*", "/", "%",
    "--", "++",
    "<", ">", "==", "+=", "-=", "*=", "/=", "%=",
    "!", "&", "|", "^", "&&", "||",
    "!=", "<=", ">=",
    "&=", "|=", "^=",
    "="};

int is_keyword(char *lexeme)
{
    for (int i = 0; i < 32; i++)
    {
        if (strcmp(lexeme, keywords[i]) == 0)
        {
            return 1;
        }
    }
    if (*lexeme == '#')
        return 1;
    return 0;
}

extern int is_special_character(char lexeme)
{
    for (int i = 0; i < 13; i++)
    {
        if (lexeme == special_characters[i])
        {
            return 1;
        }
    }
    return 0;
}

extern int is_operator(char *lexeme)
{
    for (int i = 0; i < 28; i++)
    {
        if (strcmp(lexeme, operators[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

extern int is_operator_(char c)
{
    if (c == '-' || c == '+' || c == '<' || c == '>' || c == '=' || c == '*' || c == '/' || c == '%' || c == '!' || c == '&' || c == '|' || c == '^' || c == '?')
    {
        // printf("%c is an operator\n", c);
        return 1;
    }
    return 0;
}

int is_string(char *lexeme, int len)
{
    if (*lexeme == '"' && *(lexeme + len - 1) == '"')
    {
        return 1;
    }
    else if (*lexeme == '<' && *(lexeme + len - 1) == '>')
    {
        return 1;
    }
    return 0;
}

int is_constant(char *lexeme, int len)
{
    if (strcmp(lexeme, "true") == 0 || strcmp(lexeme, "false") == 0)
    {
        return 1;
    }
    if (*lexeme == '\'' && *(lexeme + 2) == '\'' && *(lexeme + 3) == '\0')
    {
        return 1;
    }
    for (; *lexeme != '\0'; lexeme++)
    {
        if (!(*lexeme >= '0' && *lexeme <= '9' || *lexeme == '.'))
            return 0;
    }
    return 1;
}

int is_identifier(char *lexeme)
{
    if (!((*lexeme == '_') || (*lexeme >= 'a' && *lexeme <= 'z') || (*lexeme >= 'A' && *lexeme <= 'Z')))
    {
        return 0;
    }
    for (; *lexeme != '\0'; lexeme++)
    {
        if (!((*lexeme == '_') || (*lexeme >= 'a' && *lexeme <= 'z') || (*lexeme >= 'A' && *lexeme <= 'Z') || (*lexeme >= '0' && *lexeme <= '9')))
        {
            return 0;
        }
    }
    return 1;
}

struct token tokenize(char *lexeme)
{
    struct token new_token;
    int len = 0;
    char *temp = lexeme;
    char *last_type = (char *)malloc(sizeof(char) * 10);
    for (; *temp != '\0'; temp++)
    {
        len++;
    }
    new_token.value = (char *)malloc((len + 1) * sizeof(char));
    new_token.len = len;
    strcpy(new_token.value, lexeme);
    printf("Lexeme: %s\n", lexeme);
    if (is_keyword(lexeme))
    {
        new_token.type = (char *)malloc(sizeof(char) * 8);
        strcpy(new_token.type, "keyword");
        if (strcmp(lexeme, "int") == 0 || strcmp(lexeme, "float") == 0 || strcmp(lexeme, "double") == 0 || strcmp(lexeme, "char") == 0)
        {
            last_type = lexeme;
        }
    }
    else if (len == 1 && is_special_character(*lexeme))
    {
        new_token.type = (char *)malloc(sizeof(char) * 18);
        strcpy(new_token.type, "special_character");
    }
    else if (is_operator(lexeme))
    {
        new_token.type = (char *)malloc(sizeof(char) * 9);
        strcpy(new_token.type, "operator");
        // printf("Operator: %s\n", lexeme);
    }
    else if (is_string(lexeme, len))
    {
        new_token.type = (char *)malloc(sizeof(char) * 7);
        strcpy(new_token.type, "string");
    }
    else if (is_constant(lexeme, len))
    {
        new_token.type = (char *)malloc(sizeof(char) * 9);
        strcpy(new_token.type, "constant");
    }
    else if (is_identifier(lexeme))
    {
        new_token.type = (char *)malloc(sizeof(char) * 11);
        strcpy(new_token.type, "identifier");
        create_entry(lexeme);
        insert(lexeme, last_type, 0);
    }
    else
    {
        new_token.valid = 0;
        return new_token;
    };
    new_token.valid = 1;
    print_symbol_table();
    return new_token;
}

char ones_place(int n)
{
    switch (n)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    }
    return '\0';
}

char *stoi(int n, char *curr)
{
    if (n == 0)
    {
        *curr = '0';
        return curr + 1;
    }
    char *temp = (char *)malloc(32 * sizeof(char));
    char *top = temp;
    *top = 'p';
    top++;
    while (n)
    {
        *top = ones_place(n % 10);
        n /= 10;
        top++;
    }
    top--;
    for (; *top != 'p'; top--)
    {
        *curr = *top;
        curr++;
    }
    free(temp);
    return curr;
}

char *token_string(struct token temp, int lineno, int offset)
{
    // printf("\nPosition : %d %d\n", lineno, offset);
    if (strcmp(temp.value, "") == 0)
        return NULL;
    if (!temp.valid)
        return NULL;
    char *representation = (char *)malloc(sizeof(char) * 100);
    char *curr = representation;
    *curr = '<';
    curr++;
    char *ptr = temp.value;
    for (; *ptr != '\0'; ptr++)
    {
        *curr = *ptr;
        curr++;
    }
    *curr = ',';
    curr++;
    ptr = temp.type;
    for (; *ptr != '\0'; ptr++)
    {
        *curr = *ptr;
        curr++;
    }
    *curr = ',';
    curr++;
    curr = stoi(lineno, curr);
    *curr = ',';
    curr++;
    curr = stoi(offset - temp.len, curr);
    *curr = '>';
    curr++;
    *curr = '\0';
    return representation;
}