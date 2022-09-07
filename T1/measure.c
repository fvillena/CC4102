#include "edit-distance.h"

int main(int argc, char *argv[])
{
    int algorithm = atoi(argv[1]);
    char *X = argv[2];
    char *Y = argv[3];
    int result;
    if (algorithm == 1)
    {
        result = dynamic_programming_algorithm(X, Y);
    }
    else if (algorithm == 2)
    {
        result = in_cache_algorithm(X, Y);
    }
    else
    {
        result = 0;
    }
    printf("%d\n",result);
    return 0;
}