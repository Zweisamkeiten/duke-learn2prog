#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

/*
 * split to kv and store to kv pair
 */
kvpair_t * splitToKV(char * line) {
    kvpair_t * kvp= malloc(sizeof(char *) * 2);
    // locate the first '='
    char * equalIndex = strchr(line, '=');
    // copy the key
    // equalIndix - line + 1, plus 1 for the '\0'
    kvp->key = malloc(sizeof(char) * (equalIndex - line + 1));
    strncpy(kvp->key, line, equalIndex - line);
    // copy the value
    // plus 1 for '\0'
    // locate the first '\n'
    char * slashNIndex = strchr(line, '\n');
    kvp->value = malloc(sizeof(char) * (strlen(equalIndex + 1) + 1));
    strncpy(kvp->value, equalIndex + 1, slashNIndex - equalIndex - 1);
    return kvp;
}
/*
 * get every line and split to key/value pair, then add to kv array
 */
void readAndSplitToKV(kvarray_t * kvarr, FILE * fp) {
    char *curr = NULL;
    size_t sz;
    while (getline(&curr, &sz, fp) >= 0) {
        kvarr->kvarray = realloc(kvarr->kvarray, (kvarr->length + 1) * sizeof(kvpair_t *));
        kvarr->kvarray[kvarr->length] = splitToKV(curr);
        curr = NULL;
        kvarr->length = kvarr->length + 1;
    }
    free(curr);
}

/*
 * read the key/value pairs from a file
 */
kvarray_t * readKVs(const char * fname) {
    kvarray_t * kvarr = (kvarray_t *)malloc(sizeof(kvarray_t));

    // open the file
    FILE *fp = fopen(fname, "r");
    if (fp == NULL) {
        perror("Could not open the file");
        exit(EXIT_FAILURE);
    }
    readAndSplitToKV(kvarr, fp);

    return kvarr;
}

void freeKVs(kvarray_t * pairs) {
    for (int i = 0; i < pairs->length; ++i) {
        free(pairs->kvarray[i]);
    }
    free(pairs->kvarray);
    free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->length; ++i) {
      printf("key = '%s' value = '%s'\n", pairs->kvarray[i]->key, pairs->kvarray[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
    kvpair_t ** kvarr = pairs->kvarray;
    for (int i = 0; i < pairs->length; ++i) {
        if (strcmp(kvarr[i]->key, key) == 0) {
            return kvarr[i]->value;
        }
    }

    return NULL;
}
