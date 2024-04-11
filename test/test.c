// Created by aviroop on 5/4/24.
//
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
    FILE *new_fp = fopen("generated_token.txt", "w");
    fprintf(new_fp, "%s", token_stream(fp));
    fclose(fp);
    fclose(new_fp);
    remove(argv[0]);
    return 0;
}