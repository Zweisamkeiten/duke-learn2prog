#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n);

int main(int argc, char *argv[]) {
  typedef struct testArray_t {
    int array[4];
    int maxseq;
  } testArray;

  testArray test[] = {{{1, 3, 5, 7}, 4},
                      {{-1, 0, 1, 1}, 3},
                      {{9, 7, 7, 8}, 2},
                      {{-2, -1, 0, 1}, 4}};
  for (testArray *i = test; i < test + 4; ++i) {
    if (maxSeq(i->array, 4) != i->maxseq)
      return EXIT_FAILURE;
  }

  int array[0];
  if (maxSeq(array, 0) != 0)
    return EXIT_FAILURE;
  int array1[1] = {1};
  if (maxSeq(array1, 1) != 1)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
