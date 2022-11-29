#include <stdlib.h>

#include "median2.hpp"
// #include "median3.hpp"
#include <stdio.h>
#include <time.h>

int main() {
  // 1 2 3 4 5 6 *7* 8 9 10 11 15 20
  // unsigned long A[] = {3, 4, 5, 2, 1,   6, 7, 8, 9, 11,   10, 20, 15};
  // unsigned long A[] = {10, 9, 8, 1, 2, 3, 13, 12, 11, 4, 5, 6, 7};
  // int A[] = {1, 20, 3, 2, 11,   15, 10, 8, 9, 6,    4, 5, 7};
  // int A[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
  // int A[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
  int n = 100;
  int k = n / 2;
  unsigned long *A = (unsigned long*) malloc(n * sizeof(unsigned long));
  srand((unsigned)time(NULL));
  for (int i = 0; i < n; i++) {
    A[i] = rand();
    // printf("%d ",A[i]);
  }
  // int size = sizeof(A) / sizeof(A[0]);
  unsigned long m = algorithm_2(A, 0, n, k, 5);
  // std::vector<unsigned long> V;
  // for (int i = 0; i < n; i++)
  // {
  //   V.push_back(A[i]);
  // }
  // unsigned long m = algorithm_3(5, V);
  printf("%d\n", m);
}