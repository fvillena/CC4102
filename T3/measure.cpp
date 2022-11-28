#include "median.hpp"
#include "median2.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int algorithm = atoi(argv[1]);
  int n = atoi(argv[2]);
  int k = n / 2; // mediana
  int c = atoi(argv[3]);
  unsigned long *A = (unsigned long*) malloc(n * sizeof(unsigned long));
  srand((unsigned)time(NULL));
  if (strcmp(argv[4], "random") == 0) {
    for (int i = 0; i < n; i++){
      A[i] = rand();
    }
  } else {
    for (int i = 0; i < n; i++) {
      A[i] = atoi(argv[i + 4]);
    }
  }
  unsigned long result;
  unsigned long micros = 0;
  clock_t start, end;
  start = clock();
  if (algorithm == 1) {
    result = algorithm_1(A, n, k, c);
  } else if (algorithm == 2) {
    result = algorithm_2(A, 0, n, k, c);
  } else {
    result = -1;
  }
  end = clock();
  micros = end - start;
  free(A);
  printf("%d %d\n", result, micros);
  return 0;
}