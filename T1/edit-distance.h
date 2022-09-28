#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned short **Matrix;

Matrix create_matrix(unsigned short n) {
  unsigned short **rows = malloc(n * sizeof(unsigned short *));
  for (unsigned short i = 0; i < n; i++) {
    rows[i] = malloc(n * sizeof(int));
  }
  return rows;
}

typedef unsigned short *Vector;

Vector create_vector(unsigned short n) {
  unsigned short *vector = malloc(n * sizeof(unsigned short *));
  return vector;
}

void print_matrix(Matrix m, unsigned short n) {
  for (unsigned short i = 0; i < n; i++) {
    for (unsigned short j = 0; j < n; j++) {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}

unsigned short compute_southeast_edge(char *X, char *Y, unsigned short i,
                                      unsigned short j) {
  char x = X[i];
  char y = Y[j];
  // printf("%c%c ", x, y);
  if (x == y) {
    return 0;
  } else {
    return 1;
  }
}

unsigned short algorithm_1(char *X, char *Y) {
  unsigned short n = strlen(X) + 1;
  // construir la matriz
  Matrix m = create_matrix(n);
  // llenar la primera columna
  for (unsigned short i = 0; i < n; i++) {
    m[i][0] = i;
  }
  // llenar la primera fila
  for (unsigned short j = 0; j < n; j++) {
    m[0][j] = j;
  }
  // calcular el valor para cada casilla
  for (unsigned short i = 1; i < n; i++) {
    for (unsigned short j = 1; j < n; j++) {
      unsigned short north = m[i - 1][j];
      unsigned short west = m[i][j - 1];
      unsigned short northeast = m[i - 1][j - 1];
      unsigned short southeast_edge =
          compute_southeast_edge(X, Y, i - 1, j - 1);
      // printf("%d%d ", up, left);
      if (northeast <= west && northeast <= north) {
        // el valor mínimo está al noreste
        m[i][j] = northeast + southeast_edge;
      } else if (north < west && north < northeast) {
        // el valor mínimo está al norte
        m[i][j] = north + 1;
      } else {
        // el valor mínimo está al oeste
        m[i][j] = west + 1;
      }

      // printf("%d ", southeast_edge);
    }
    // printf("\n");
  }
  // printf("\n");
  // imprimir la matriz
  // print_matrix(m, n);
  return m[n - 1][n - 1];
}

unsigned short compute_cell(unsigned short northeast, unsigned short west,
                            unsigned short north,
                            unsigned short southeast_edge) {
  unsigned short result;
  if (northeast <= west && northeast <= north) {
    // el valor mínimo está al noreste
    result = northeast + southeast_edge;
  } else if (north < west && north < northeast) {
    // el valor mínimo está al norte
    result = north + 1;
  } else {
    // el valor mínimo está al oeste
    result = west + 1;
  }
  return result;
}

unsigned short algorithm_2(char *X, char *Y) {
  unsigned short n = strlen(X) + 1;
  Vector row = create_vector(n);
  Vector column = create_vector(n);
  unsigned short last_west;
  unsigned short last_northeast;
  unsigned short last_north;
  for (unsigned short i = 0; i < n; i++) {
    row[i] = i;
    column[i] = i;
    // printf("%d %d\n", row[i], column[i]);
  }

  for (unsigned short k = 1; k < n; k++) {
    for (unsigned short i = k; i < n; i++) {
      if (i == k) {
        last_west = column[k];
        last_northeast = row[k - 1];
      }
      unsigned short west = last_west;
      unsigned short northeast = last_northeast;
      unsigned short north = row[i];
      unsigned short southeast_edge =
          compute_southeast_edge(X, Y, k - 1, i - 1);
      unsigned short cell =
          compute_cell(northeast, west, north, southeast_edge);
      // printf("[%d, %d] = %d\n", k, i, northeast, north, last_west, cell);
      last_west = cell;
      last_northeast = row[i];
      row[i] = cell;
    }
    for (unsigned short j = k + 1; j < n; j++) {
      if (j - k == 1) {
        last_north = row[k];
        last_northeast = column[j - 1];
      }
      unsigned short north = last_north;
      unsigned short northeast = last_northeast;
      unsigned short west = column[j];
      unsigned short southeast_edge =
          compute_southeast_edge(X, Y, j - 1, k - 1);
      unsigned short cell =
          compute_cell(northeast, west, north, southeast_edge);
      // printf("[%d, %d] = %d\n", j, k, cell);
      last_north = cell;
      last_northeast = column[j];
      column[j] = cell;
    }
  }
  return row[n - 1];
}