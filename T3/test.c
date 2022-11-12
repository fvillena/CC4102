#include "median.h"
#include "stdio.h"

void main() {
  // 1 2 3 4 5 6 *7* 8 9 10 11 15 20
  // int A[] = {3, 4, 5, 2, 1,   6, 7, 8, 9, 11,   10, 20, 15};
  // int A[] = {1, 20, 3, 2, 11,   15, 10, 8, 9, 6,    4, 5, 7};
  int A[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
  int size = sizeof(A) / sizeof(A[0]);
  int m = algorithm_1(A, size, 6, 5);

  printf("%d\n", m);
}