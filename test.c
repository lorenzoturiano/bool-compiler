#include <stdio.h>
#include <string.h>
#define MAX_CHAR 50
#define MAX_SIZE 50
#define MAX_TOK 1000

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

int main() {
    char tokens[50][MAX_CHAR+1] = {"z", "=", "x1", "or", "x2", ";"};
    char keys[MAX_SIZE][MAX_CHAR+1];
    char values[MAX_SIZE][MAX_TOK][MAX_CHAR+1];
    int current_size = 0;
    int i=0;
    parseAssign(tokens, &i, &current_size, keys, values);
    printf("{key: %s\nvalue: %s}\n", keys[current_size], values[current_size][0]);
    return 0;
}