#include "edit-distance.h"
#include <time.h>

int main(int argc, char *argv[])
{
    int algorithm = atoi(argv[1]);
    char *X = argv[2];
    char *Y = argv[3];
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
    else
    {
        result = 0;
    }
    end = clock();
    micros = end - start;
    printf("%d %d\n",result, micros);
    return 0;
}