#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 10
#define LINE_SIZE 12

void reverse_line(char line[][10]) {
  char *p = line[0], *q = line[0] + 9;
  while (p <= q) {
    char temp = *q;
    *q = *p;
    *p = temp;
    ++p;
    --q;
  }
  return;
}

void oblique_symmetry(char matrix[10][10]) {
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10 - i; ++j) {
      char temp = matrix[i][j];
      matrix[i][j] = matrix[9 - j][9 - i];
      matrix[9 - j][9 - i] = temp;
    }
  }
  return;
}

void rotate(char matrix[10][10]) {
  for (int i = 0; i < 10; ++i) {
    reverse_line(matrix + i);
  }
  oblique_symmetry(matrix);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: read-matrix input\n");
    exit(EXIT_FAILURE);
  }

  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    fprintf(stderr, "Could not open %s\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  char matrix[MATRIX_SIZE][MATRIX_SIZE] = {0};
  int row = 0;
  char line[LINE_SIZE];
  int index = 0;
  char *newline;
  char *read;
  while ((read = fgets(line, LINE_SIZE, fp)) != NULL) {
    if ((newline = strchr(line, '\n')) != NULL) {
      if (newline - line == 10) {
        row++;
        for (int i = 0; i < MATRIX_SIZE; ++i) {
          *((*matrix) + index) = line[i];
          index++;
        }
        continue;
      }
      if (index == MATRIX_SIZE * MATRIX_SIZE) {
        fprintf(stderr,
                "Invalid input: file is too long (read %d instead of EOF)\n",
                line[0]);
        exit(EXIT_FAILURE);
      }

      if (newline - line < 10) {
        fprintf(stderr, "Invalid input: Line is too short\n");
        exit(EXIT_FAILURE);
      }
    } else {
      fprintf(stderr, "Invalid input: Line is too long\n");
      exit(EXIT_FAILURE);
    }
  }

  if (row != MATRIX_SIZE) {
    fprintf(stderr, "Invalid input: line is too short\n");
    exit(EXIT_FAILURE);
  }

  rotate(matrix);
  for (int i = 0; i < MATRIX_SIZE; ++i) {
    for (int j = 0; j < MATRIX_SIZE; ++j) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}
