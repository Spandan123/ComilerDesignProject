//
// Created by aviroop on 5/4/24.
//

#ifndef FINAL_ASSIGNMENT_LEXEME_H
#define FINAL_ASSIGNMENT_LEXEME_H

#endif // FINAL_ASSIGNMENT_LEXEME_H
#include <stdio.h>
#include <stdlib.h>
// #include "lexer.h"

int lineno = 1;
int offset = 0;

char *generate_lexeme(FILE *fp)
{
    if (!fp)
    {
        printf("Invalid file pointer!\n");
        return NULL;
    }
    char *lexeme = (char *)malloc(1024 * sizeof(char));
    char *top = lexeme;
    int in_string = 0;
    while (1)
    {
        char c = fgetc(fp);
        if (in_string)
        {
            *top = c;
            top++;
            if (c == '"')
            {
                in_string = 0;
                *top = '\0';
                return lexeme;
            }
        }
        else if (!in_string && c == '"')
        {
            *top = c;
            top++;
            in_string = 1;
        }
        else if (c == '\n')
        {
            lineno++;
            offset = 0;
            break;
        }
        else if (c == '\t')
        {
            offset += 4;
            break;
        }
        else if (c == ' ')
        {
            offset++;
            break;
        }
        else if (c == EOF)
        {
            lineno = 1;
            offset = 0;
            break;
        }
        else if (c == '#' && top == lexeme)
        {
            *top = '#';
            top++;
            while ((c = getc(fp)) == ' ')
            {
            }
            while ((c == '.') || (c != EOF) && !is_operator_(c) && !is_special_character(c) && c != '\n' && c != ' ')
            {
                *top = c;
                top++;
                c = fgetc(fp);
            }
            ungetc(c, fp);
            *top = '\0';
            return lexeme;
        }
        else if (c == '<' && top == lexeme)
        {
            *top = c;
            top++;
            int prob_unget = 0;
            c = fgetc(fp);
            while ((c == '.') || (c != EOF) && !is_operator_(c) && !is_special_character(c) && c != '\n' && c != ' ' && c != '>')
            {
                *top = c;
                top++;
                c = fgetc(fp);
                prob_unget++;
            }
            if (c == '>')
            {
                prob_unget = 0;
                *top = '>';
                top++;
            }
            else
            {
                *(lexeme + 1) = '\0';
            }
            for (int i = 0; i < prob_unget; i++)
                ungetc(c, fp);
            *top = '\0';
            return lexeme;
        }
        else if (is_special_character(c))
        {
            if (top == lexeme)
            {
                *top = c;
                top++;
            }
            else
            {
                ungetc(c, fp);
            }
            break;
        }
        else if (is_operator_(c))
        {
            if (top == lexeme)
            {
                *top = c;
                top++;
                c = fgetc(fp);
                if (is_operator_(c))
                {
                    *top = c;
                    top++;
                }
                else
                {
                    ungetc(c, fp);
                }
            }
            break;
        }
        else
        {
            *top = c;
            top++;
        }
    }
    *top = '\0';
    return lexeme;
}