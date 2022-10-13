#include <stddef.h>
#include <stdio.h>

size_t maxSeq(int *array, size_t n) {
  if (n == 0 || n == 1)
    return n;
  int maxseq = 1;
  int tempseq = 1;
  for (int i = 1; i < n; ++i) {
    if (array[i] > array[i - 1]) {
      tempseq += 1;
      if (tempseq > maxseq)
        maxseq = tempseq;
    } else
      tempseq = 1;
  }
  return maxseq;
}
