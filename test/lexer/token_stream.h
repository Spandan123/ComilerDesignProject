#include <string.h>
#include <stdlib.h>
#include "lexer.h"
#include "lexeme.h"
#define MAX(x, y) ((x) > (y) ? (x) : (y))
char *token_stream(FILE *fp)
{
    if (!fp)
    {
        printf("Invalid file pointer!\n");
        return "";
    }
    fseek(fp, 0, SEEK_SET);
    char *buffer = (char *)malloc(1024 * sizeof(char));
    *buffer = '\0';
    while (!feof(fp))
    {
        struct token t = tokenize(generate_lexeme(fp));
        char *s = token_string(t, lineno, offset);
        if (!s)
            continue;
        // printf("\n\nToken received : %s\n", s);
        int val_start = 1;
        int val_end = 2;
        while (s[val_end] != ',')
            val_end++;
        int val_len = val_end - val_start;
        // printf("val_start = %d, val_end = %d, val_len = %d\n", val_start, val_end, val_len);
        int type_start = val_end + 1;
        int type_end = type_start + 1;
        while (s[type_end] != ',')
            type_end++;
        int type_len = type_end - type_start;
        // printf("type_start = %d, type_end = %d, type_len = %d\n", type_start, type_end, type_len);
        char *val = (char *)malloc(sizeof(char) * val_len + 1);
        char *type = (char *)malloc(sizeof(char) * type_len + 1);
        strncpy(val, s + val_start, val_len);
        strncpy(type, s + type_start, type_len);
        if (strlen(buffer) + MAX(val_len, type_len) + 2 >= 1024)
        {
            buffer = (char *)realloc(buffer, sizeof(char) * (1024 + strlen(buffer)));
        }
        if (strcmp(type, "identifier") == 0)
        {
            strcat(buffer, "id ");
            // printf("id appended!");
        }
        else if (strcmp(type, "constant") == 0 || strcmp(type, "string") == 0)
        {
            strcat(buffer, "val ");
            // printf("val appended!");
        }
        else
        {
            strcat(buffer, val);
            strcat(buffer, " ");
            // printf("%s appended!", val);
        }
    }
    return buffer;
}