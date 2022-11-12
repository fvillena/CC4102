#include "quicksort.h"

int median(int A[], int size) {
  int k = (size + 1) / 2;
  quickSort(A, 0, size - 1);
  return A[k - 1];
}

int algorithm_1(int A[], int size, int k, int c) {
  int c_remainder = size % c;
  // int i = size / 2;
  int sublist_n = (size + c - 1) / c;
  int sublist[sublist_n][c];
  for (int i = 0; i < sublist_n; i++) {
    for (int j = 0; j < c; j++) {
      int A_position = i * c + j;
      if (A_position >= size) {
        sublist[i][j] = -1;
      } else {
        sublist[i][j] = A[A_position];
      }
    }
  }
  int medians[sublist_n];
  for (int i = 0; i < sublist_n; i++) {
    if (i != sublist_n - 1) {
      medians[i] = median(sublist[i], c);
    } else {
      int A_remainder[c_remainder];
      for (int j = 0; j < c_remainder; j++) {
        A_remainder[j] = sublist[i][j];
      }
      medians[i] = median(A_remainder, c_remainder);
    }
  }
  int pivot;
  if (sublist_n <= c) {
    pivot = median(medians, sublist_n);
  } else {
    pivot = algorithm_1(medians, sublist_n, sublist_n / 2, c);
  }
  int low[size];
  int low_n = 0;
  int high[size];
  int high_n = 0;
  for (int i = 0; i < size; i++) {
    if (A[i] < pivot) {
      low[i] = A[i];
      low_n++;
      high[i] = -1;
    } else if (A[i] > pivot) {
      high[i] = A[i];
      high_n++;
      low[i] = -1;
    } else {
      high[i] = -1;
      low[i] = -1;
    }
  }
  if (k < low_n) {
    int A_low[low_n];
    int j = 0;
    for (int i = 0; i < size; i++) {
      if (low[i] != -1) {
        A_low[j] = low[i];
        j++;
      }
    }
    return algorithm_1(A_low, low_n, k, c);

  } else if (k > low_n) {
    int A_high[high_n];
    int j = 0;
    for (int i = 0; i < size; i++) {
      if (high[i] != -1) {
        A_high[j] = high[i];
        j++;
      }
    }
    return algorithm_1(A_high, high_n, k - low_n - 1, c);
  } else {
    return pivot;
  }
}