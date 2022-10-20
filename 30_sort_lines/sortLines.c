#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function is used to figure out the ordering
// of the strings in qsort.  You do not need
// to modify it.
int stringOrder(const void *vp1, const void *vp2) {
  const char *const *p1 = vp1;
  const char *const *p2 = vp2;
  return strcmp(*p1, *p2);
}
// This function will sort and print data (whose length is count).
void sortData(char **data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void readTheInput(FILE *stream) {
    char **lines = NULL;
    size_t length = 0;
    char *curr = NULL;
    size_t sz;
    while (getline(&curr, &sz, stream) >= 0) {
        lines = realloc(lines, (length + 1) * sizeof(*lines));
        lines[length] = curr;
        curr = NULL;
        length++;
    }
    free(curr);
    sortData(lines, length);
    for (size_t j = 0; j < length; ++j) {
        printf("%s", lines[j]);
        free(lines[j]);
    }
    free(lines);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        readTheInput(stdin);
    } else {
        for (int i = 1; i < argc; ++i) {
            FILE *f = fopen(argv[i], "r");
            if (f == NULL) {
                perror("Could not open file");
                return EXIT_FAILURE;
            }
            readTheInput(f);
            if (fclose(f) != 0) {
                perror("Failed to close the input file!");
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}
