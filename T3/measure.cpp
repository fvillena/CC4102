#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

#include "median.hpp"
// #include "median2.hpp"

int main(int argc, char *argv[]) {
  int algorithm = atoi(argv[1]);
  int n = atoi(argv[2]);
  int c = atoi(argv[3]);
  unsigned long *A = (unsigned long *)malloc(n * sizeof(unsigned long));
  srand((unsigned)time(NULL));
  if (strcmp(argv[4], "random") == 0) {
    for (int i = 0; i < n; i++) {
      A[i] = rand();
    }
  } else {
    for (int i = 0; i < n; i++) {
      A[i] = atoi(argv[i + 4]);
    }
  }
  int k = n / 2;  // mediana
  unsigned long result;
  unsigned long micros = 0;
  clock_t start, end;
  if (algorithm == 1) {
    start = clock();
    result = algorithm_1(A, n, k, c);
    end = clock();
    micros = end - start;
    printf("%d %d\n", result, micros);
  } else if (algorithm == 2) {
    start = clock();
    result = algorithm_2(A, 0, n, k, c);
    end = clock();
    micros = end - start;
    printf("%d %d\n", result, micros);
  } else if (algorithm == 3) {
    std::vector<unsigned long> V;
    for (int i = 0; i < n; i++) {
      V.push_back(A[i]);
    }
    start = clock();
    result = algorithm_3(c, V);
    end = clock();
    micros = end - start;
    printf("%d %d\n", result, micros);
  } else {
    result = -1;
  }
  free(A);
  return 0;
}