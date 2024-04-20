// Created by aviroop on 5/4/24.
//
#include "lexer/token_stream.h"
#include "parser/parser.h"
#include "parser/LR1_automaton.h"
#include "parser/parsing_table.h"
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
    FILE *new_fp = fopen("actual.txt", "r");
    char *x = (char *)malloc(sizeof(char) * 1024);
    fscanf(new_fp, "%[^\n]s", x);
    cout << x;
    // x = token_stream(fp);
    // fprintf(new_fp, "%s", x);
    fclose(fp);
    fclose(new_fp);
    run_parser();
    // printMap(first);
    // printf("\n\n");
    // printMap(follow);
    LR1_item_set::create_LR1_automaton();
    // print_item_mapping();
    create_parsing_table();
    // print_parsing_table();
    cout << "\n\nToken stream : \n"
         << x << "\n\n";
    parse(x);
    remove(argv[0]);
    return 0;
}