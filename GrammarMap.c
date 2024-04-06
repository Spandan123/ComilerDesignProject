#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fp;
    int linenum = 0;
    char filename[] = "cfg.txt";
    char line[500];
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("can't open file");
        exit(1);
    }
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // line[strcspn(line, "\n")] = 0;
        linenum++;
        // if (strlen(line) > 0)
        printf("%s  %d\n", line, linenum);
    }
}