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
    // abs('e' - 'a' - largest_index) wrong 因为当找到的最频繁字母索引如果小于e, 例如是c, 它是加密前的字母加key超过26取余获得的
    int key = (largest_index + 26 - ('e' - 'a')) % 26;
    return key;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: breaker inputFileName\n");
        return EXIT_FAILURE;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }
    int alphalist[ALPHA_LIST_LENGTH] = {0};
    int key = breaker(fp, alphalist);
    printf("%d\n", key);
    if (fclose(fp) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
