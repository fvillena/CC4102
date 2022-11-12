#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "median.h"

int main(int argc, char *argv[]) {
  int algorithm = atoi(argv[1]);
  int n = atoi(argv[2]);
  int k = n / 2;
  int c = atoi(argv[3]);
  int A[n];
  for (int i = 0; i < n; i++) {
    A[i] = atoi(argv[i + 4]);
  }
  int result;
  unsigned long micros = 0;
  clock_t start, end;
  start = clock();
  if (algorithm == 1) {
    result = algorithm_1(A, n, k, c);
  } else {
    result = -1;
  }
  end = clock();
  micros = end - start;
  printf("%d %d\n", result, micros);
  return 0;
}