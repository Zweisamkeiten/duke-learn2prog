#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
    counts_t * c = createCounts();
    char ** names = NULL;
    int length = 0;
    char * curr = NULL;
    size_t sz = 0;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Could not open the file");
        exit(EXIT_FAILURE);
    }
    while (getline(&curr, &sz, fp) >= 0) {
        names = realloc(names, (length + 1) * sizeof(char *));
        names[length] = curr;
        curr = NULL;
        length++;
    }
    free(curr);
    if (fclose(fp) != 0) {
        perror("Failed to close the input file!");
        exit(EXIT_FAILURE);
    }

    int foundFlag = 0;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < kvPairs->length; ++j) {
            // strlen(names[i]) - 1 because it is '\n' after getline
            if (strncmp(names[i], kvPairs->kvarray[j]->key, strlen(names[i]) - 1) == 0) {
                foundFlag = 1;
                addCount(c, kvPairs->kvarray[j]->value);
            }
        }
        if (foundFlag == 0) {
            addCount(c, NULL);
        }
        foundFlag = 0;
        // free it
        free(names[i]);
    }
    free(names);
    return c;
}

int main(int argc, char ** argv) {
    //WRITE ME (plus add appropriate error checking!)
    //read the key/value pairs from the file named by argv[1] (call the result kv)
    if (argc < 3) {
        fprintf(stderr, "Usage: ./count_values kvs.txt list.txt\n");
        return EXIT_FAILURE;
    }
    kvarray_t * array = readKVs(argv[1]);
    //count from 2 to argc (call the number you count i)
    for (int i = 2; i < argc; ++i) {
        //count the values that appear in the file named by argv[i], using kv as the key/value pair
        //   (call this result c)
        counts_t * c = countFile(argv[i], array);
        //compute the output file name from argv[i] (call this outName)
        char * outFileName = computeOutputFileName(argv[i]);
        //open the file named by outName (call that f)
        FILE *fp = fopen(outFileName, "w");
        if (fp == NULL) {
            perror("Could not open the file.");
            return EXIT_FAILURE;
        }
        //print the counts from c into the FILE f
        printCounts(c, fp);
        //close f
        if (fclose(fp) != 0) {
            perror("Failed to close the input file!");
            return EXIT_FAILURE;
        }
        //free the memory for outName and c
        freeCounts(c);
        free(outFileName);
    }
    //free the memory for kv
    freeKVs(array);
    return EXIT_SUCCESS;
}
