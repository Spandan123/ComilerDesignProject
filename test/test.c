//
// Created by aviroop on 5/4/24.
//
#include <stdio.h>
#include <stdlib.h>
#include "lexer/lexer.h"
#include "lexer/lexeme.h"
int main(int argc, char *argv[])
{
    char *ffp = "test/test.txt";
    FILE *fp = fopen(ffp, "r");
    if (!fp)
    {
        printf("File cannot be opened!\n");
        remove(argv[0]);
        exit(1);
    }
    char *s = NULL;
    while (!feof(fp))
    {
        s = token_string(tokenize(generate_lexeme(fp), lineno, offset));
        if (s)
        {
            printf("%s\n", s);
        }
        else
        {
            // printf("\nInvalid lexeme at line %d in position %d!\n", lineno, offset + 1);
        }
    }
    fclose(fp);
    remove(argv[0]);
    return 0;
}