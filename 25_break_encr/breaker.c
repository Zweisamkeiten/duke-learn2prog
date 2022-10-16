#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define ALPHA_LIST_LENGTH 26

int find_the_largest_item_index(int * s, size_t length) {
    int largest = s[0];
    int largest_index = 0;
    for (int i = 1; i < length; ++i) {
        if (s[i] > largest) {
            largest = s[i];
            largest_index = i;
        }
    }
    return largest_index;
}
int breaker(FILE * fp, int * alphalist) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if(isalpha(c)) {
            c = tolower(c);
            c -= 'a';
            alphalist[c] += 1;
        }
    }
    int largest_index = find_the_largest_item_index(alphalist, ALPHA_LIST_LENGTH);
    int key = abs('e' - 'a' - largest_index);
    return key;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: breaker inputFileName\n");
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    int alphalist[ALPHA_LIST_LENGTH] = {0};
    int key = breaker(fp, alphalist);
    printf("%d\n", key);
    return 0;
}
