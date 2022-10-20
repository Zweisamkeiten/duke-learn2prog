#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
/*
 * init the counts
 */
counts_t * createCounts(void) {
    counts_t * con = malloc(sizeof(counts_t));
    con->size = 0;
    con->counts = NULL;
    return con;
}
/*
 * increment the count for the corresponding name
 */
void addCount(counts_t * c, const char * name) {
    if (name == NULL) {
        name = "<unknown>";
    }
    for (int i = 0; i < c->size; ++i) {
        if (strcmp(c->counts[i]->info, name) == 0) {
            c->counts[i]->counts = c->counts[i]->counts + 1;
            return;
        }
    }
    c->counts = realloc(c->counts, (c->size + 1) * sizeof(one_count_t *));
    c->counts[c->size] = calloc(1, sizeof(one_count_t));
    char * copy = calloc(1, sizeof(char) * (strlen(name) + 1));
    strcpy(copy, name);
    c->counts[c->size]->info = copy;
    c->counts[c->size]->counts = 1;
    c->size = c->size + 1;
}
void printCounts(counts_t * c, FILE * outFile) {
    int unknownIndex = -1;
    for (int i = 0; i < c->size; ++i) {
        // or for always false to make this un-zero unknown line print last;
        if (strcmp(c->counts[i]->info, "<unknown>") != 0 || ((unknownIndex = i) && 0)) {
            fprintf(outFile, "%s: %d\n", c->counts[i]->info, c->counts[i]->counts);
        }
    }
    if (unknownIndex != -1) {
        fprintf(outFile, "%s : %d\n", c->counts[unknownIndex]->info, c->counts[unknownIndex]->counts);
    }
}

void freeCounts(counts_t * c) {
    for (int i = 0; i < c->size; ++i) {
        free(c->counts[i]->info);
        free(c->counts[i]);
    }
    free(c->counts);
    free(c);
}
