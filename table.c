// We consider that a line is not longer than 500 characters.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_CHAR 20
#define MAX_TOK 1000
#define MAX_DECL_VAR 30


int isSpecialChar(char c) {
    if (c == ';' || c == '(' || c == ')' || c == '#')
        return 1;
    else
        return 0;
}

int stringIsAlnum(char s[MAX_CHAR+1]) {
    int l = strlen(s);
    int i = 0;
    int flag = 1;
    while (i < l && flag == 1) {
        if (!isalnum(s[i]))
            flag = 0;
        i++;
    }
    return flag;
}

void getTokens(char tokens[][MAX_CHAR+1], FILE *f, int *tk_size) {
    int j = 0;
    int c_i;
    char c;
    int comment = 0;

    while ((c_i = fgetc(f)) != EOF && j < MAX_TOK) {
        c = (char)c_i;

        if (c == '#')
            comment = 1;
        if (c == '\n')
            comment = 0;

        if (comment == 0) {
            // 1) skip whitespace
            if (isspace((unsigned char)c)) {
                continue;
            }

            // 2) single‐char token?
            if (isSpecialChar(c)) {
                tokens[j][0] = c;
                tokens[j][1] = '\0';
                j++;
                continue;
            }

            // 3) multi‐char token: read until your delimiter
            int idx = 0;
            do {
                if (idx < MAX_CHAR)
                    tokens[j][idx++] = c;

                c_i = fgetc(f);
                if (c_i == EOF) break;
                c = (char)c_i;
            } while (!isspace((unsigned char)c)
                && !isSpecialChar(c));

            tokens[j][idx] = '\0';
            j++;

            // 4) if we stopped on a special char, handle it too
            if (c_i != EOF && isSpecialChar(c) && j < MAX_TOK) {
                tokens[j][0] = c;
                tokens[j][1] = '\0';
                j++;
            }
        }
    }
    *tk_size = j;
}


int isAssign(char tokens[][MAX_CHAR+1], int count, int *i) {
    // int flag = 0;
    // int j = 0;
    // if (strcmp(tokens[*i], "=") == 0) {
    //     while (tokens[(*i)-1][j] != '\0' && flag == 0) {
    //         if (!isalnum(tokens[(*i)-1][j]))
    //             flag = 1;
    //         j++;
    //     }

    //     if (flag == 1)
    //         return 0;
    //     else
    //         return 1;
    // } else 
    //     return 0;

    return 0;
}

void parseVarDecl(char tokens[][MAX_CHAR+1], int count, int *i, char decl_vars[][MAX_CHAR+1], int *n_decl_vars) {
    while (*i < count && strcmp(tokens[*i], ";") != 0) {
        if (*n_decl_vars < MAX_DECL_VAR) {
            strcpy(decl_vars[*n_decl_vars-1], tokens[*i]);
            (*n_decl_vars)++;
        } else {
            printf("Max number of declarable vars exceeded.\n");
        }
        (*i)++;
    }
}

void parseTokens(char tokens[][MAX_CHAR+1], int count, char decl_vars[][MAX_CHAR+1], int *n_decl_vars) {
    int i = 0;
    while (i<count) {
        printf("(%d, %s)\n", i, tokens[i]);

        if (strcmp("var", tokens[i]) == 0) {
            parseVarDecl(tokens, count, &i, decl_vars, n_decl_vars);
        }

        int k = isAssign(tokens, count, &i);
        printf("%d\n", k);
        i++;
    }
}


int main() {
    FILE *f = fopen("hw01_instances/ag10_00.txt", "r");
    
    if (f != NULL) {
        char tokens[MAX_TOK][MAX_CHAR+1];
        char decl_vars[MAX_DECL_VAR][MAX_CHAR+1];
        int n_tokens, n_decl_vars = 0;

        // I have an array of tokens to work with
        getTokens(tokens, f, &n_tokens);
        // for (int i=0; i<count; i++)
        //     printf("%s\n", tokens[i]);

        parseTokens(tokens, n_tokens, decl_vars, &n_decl_vars);

    } else {
        printf("Error: invalid file.\n");
    }

    return 0;
}