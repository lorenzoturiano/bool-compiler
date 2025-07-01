// We consider that a line is not longer than 500 characters.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_CHAR 20
#define MAX_TOK 1000
#define MAX_DECL_VAR 30
#define MAX_SIZE 50

void showTruthTable(char var[], char k[][MAX_CHAR+1], char v[][MAX_TOK][MAX_CHAR+1], int *curr_size) {
    return;
}

void showonesTruthTable(char var[], char k[][MAX_CHAR+1], char v[][MAX_TOK][MAX_CHAR+1], int *curr_size) {
    return;
}

int getIndex(char s[], char k[][MAX_CHAR+1], int *curr_size) {
    int i = 0;
    while (i<*curr_size) {
        if (strcmp(k[i], s) == 0)
            return i;
    }
    return -1;
}

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
    if (stringIsAlnum(tokens[*i]) && strcmp(tokens[*i+1], "=") == 0)
        return 1;
    else    
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

void parseAssign(char tokens[][MAX_CHAR+1], int *i, char k[][MAX_CHAR+1], char v[][MAX_TOK][MAX_CHAR+1], int *curr_size) {
    strcpy(k[*curr_size], tokens[*i]);
    (*i) = (*i)+2;
    int j = 0;

    while (strcmp(tokens[*i], ";") != 0) {
        strcpy(v[*curr_size][j], tokens[*i]);
        (*i)++;
        j++;
    }
    (*curr_size)++;
}

void parseShow(char tokens[][MAX_CHAR+1], int *i, char k[][MAX_CHAR+1], char v[][MAX_TOK][MAX_CHAR+1], int *curr_size) {
    int cmnd_idx = *i;
    int idx;
    (*i)++;
    while (strcmp(tokens[*i], ";") != 0) {
        idx = getIndex(tokens[*i], k, curr_size);
        if (idx != -1) {
            if (strcmp(tokens[cmnd_idx], "show") == 0)
                showTruthTable(tokens[*i], k, v, curr_size);
            if(strcmp(tokens[cmnd_idx], "show_ones") == 0)
                showonesTruthTable(tokens[*i], k, v, curr_size);
        } else return;
        (*i)++;
    }
}

void parseTokens(char tokens[][MAX_CHAR+1], int count, char decl_vars[][MAX_CHAR+1], int *n_decl_vars, char k[][MAX_CHAR+1], char v[][MAX_TOK][MAX_CHAR+1], int *curr_size) {
    int i = 0;
    while (i<count-1) {
        // printf("(%d, %s)\n", i, tokens[i]);

        if (strcmp("var", tokens[i]) == 0) {
            parseVarDecl(tokens, count, &i, decl_vars, n_decl_vars);
        }

        if (isAssign(tokens, count, &i)) {
            parseAssign(tokens, &i, k, v, curr_size);
            // printf("%s\n\n", tokens[i]);
        }

        if (strcmp("show", tokens[i]) == 0 || strcmp("show_ones", tokens[i]) == 0) {            
            // printf("%s\n", tokens[i]);            
            parseShow(tokens, &i, k, v, curr_size);
        }
        
        i++;
    }
}


int main() {
    FILE *f = fopen("hw01_instances/ag10_00.txt", "r");
    
    if (f != NULL) {
        char tokens[MAX_TOK][MAX_CHAR+1];
        char decl_vars[MAX_DECL_VAR][MAX_CHAR+1];
        int n_tokens, n_decl_vars = 0;

        char keys[MAX_SIZE][MAX_CHAR+1];
        char values[MAX_SIZE][MAX_TOK][MAX_CHAR+1];
        int current_size = 0;

        // I have an array of tokens to work with
        getTokens(tokens, f, &n_tokens);
        // Uncomment to print all the tokens
        // for (int i=0; i<n_tokens; i++)
        //     printf("%s\n", tokens[i]);

        parseTokens(tokens, n_tokens, decl_vars, &n_decl_vars, keys, values, &current_size);

    } else {
        printf("Error: invalid file.\n");
    }

    return 0;
}