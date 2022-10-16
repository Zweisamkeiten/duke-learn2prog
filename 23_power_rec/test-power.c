#include <stdlib.h>
#include <stdio.h>

unsigned power(unsigned x, unsigned y);

int main(int argc, char *argv[])
{
    typedef struct test_t
    {
        unsigned x;
        unsigned y;
        unsigned ans;
    } test;

    test tests[] = {{0, 0, 1}, {-1, 2, 1}, {-1, 3, -1}, {1, 1, 1}, {-2, 2, 4}, {0, 0, 0}};
    test * p = tests;
    while (p->x+p->y+p->ans != 0) {
        if (power(p->x, p->y) != p->ans) {
            exit(EXIT_FAILURE);
        }
        ++p;
    }
    return EXIT_SUCCESS;
}
