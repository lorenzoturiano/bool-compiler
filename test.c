#include <stdio.h>
#include <string.h>
#define MAX_CHAR 50
#define MAX_SIZE 50
#define MAX_TOK 1000
#define MAX_NODE 1000

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

void parseAssign(char tokens[][MAX_CHAR+1], int *i, int *size, char k[][MAX_CHAR+1], char v[][MAX_TOK][MAX_CHAR+1]) {
    strcpy(k[*size], tokens[*i]);
    (*i) = (*i)+2;
    int j = 0;

    while (strcmp(tokens[*i], ";")) {
        strcpy(v[*size][j], tokens[*i]);
        (*i)++;
        j++;
    }
}

void buildTree(char tokens[][MAX_CHAR+1], int *n_tokens, char tree[][MAX_CHAR+1]){
    int i = 1;
    int j = 0;

    while (j < *n_tokens) {
        if (strcmp(tokens[j], "or") == 0 || strcmp(tokens[j], "and") == 0) {
            if (


        }



        j++;
    }
    // Base case





}
int main() {
    char tokens[MAX_TOK][MAX_CHAR+1] = {"x1", "or", "(", "(", "x2", "or", "x3", ")", "and", "(", "x4", "or", "x5", ")", "and", "(", "x6", "and", "x7", ")", ")"};
    int n_tokens = 21;
    char keys[MAX_SIZE][MAX_CHAR+1];
    char values[MAX_SIZE][MAX_TOK][MAX_CHAR+1];
    char tree[MAX_NODE][MAX_CHAR+1];
    
    int current_size = 0;
    int i=0;


    return 0;
}