#include "edit-distance.h"
#include <time.h>

int main(int argc, char *argv[])
{
    int algorithm = atoi(argv[1]);
    int sub_matrix_size;
    char *X;
    char *Y;
    if (algorithm == 3)
    {
        sub_matrix_size = atoi(argv[2]);
        X = argv[3];
        Y = argv[4];
    }
    else
    {
        X = argv[2];
        Y = argv[3];
    }

    int result;
    unsigned long micros = 0;
    clock_t start, end;
    start = clock();
    if (algorithm == 1)
    {
        result = algorithm_1(X, Y);
    }
    else if (algorithm == 2)
    {
        result = algorithm_2(X, Y);
    }
    else if (algorithm == 3)
    {
        result = algorithm_3(X, Y, sub_matrix_size);
    }
    else
    {
        result = 0;
    }
    end = clock();
    micros = end - start;
    printf("%d %d\n", result, micros);
    return 0;
}