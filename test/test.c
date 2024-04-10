//
// Created by aviroop on 5/4/24.
//
#include <stdio.h>
#include <stdlib.h>
#include "lexer/token_stream.h"

int main(int argc, char *argv[])
{
    char *ffp = "test.txt";
    FILE *fp = fopen(ffp, "r");
    if (!fp)
    {
        printf("File cannot be opened!\n");
        remove(argv[0]);
        exit(1);
    }
    printf("\n%s\n", token_stream(fp));
    fclose(fp);
    remove(argv[0]);
    return 0;
}