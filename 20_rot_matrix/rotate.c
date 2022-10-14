void reverse_line(char line[][10]) {
    char * p = line[0], *q = line[0] + 9;
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
            matrix[i][j] = matrix[9-j][9-i];
            matrix[9-j][9-i] = temp;
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
