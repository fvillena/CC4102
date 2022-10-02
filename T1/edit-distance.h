#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estructura para definir una matriz en el heap
typedef unsigned short **Matrix;
Matrix create_matrix(unsigned short n)
{
  unsigned short **rows = malloc(n * sizeof(unsigned short *));
  for (unsigned short i = 0; i < n; i++)
  {
    rows[i] = malloc(n * sizeof(unsigned short));
  }
  return rows;
}

// estructura para definir un vector en el heap
typedef unsigned short *Vector;
Vector create_vector(unsigned short n)
{
  unsigned short *vector = malloc(n * sizeof(unsigned short *));
  return vector;
}

// cálculo de la arista sureste
unsigned short compute_southeast_edge(char *X, char *Y, unsigned short i,
                                      unsigned short j)
{
  char x = X[i];
  char y = Y[j];
  if (x == y)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

// calcular el valor de la celda
unsigned short compute_cell(unsigned short northeast, unsigned short west,
                            unsigned short north,
                            unsigned short southeast_edge)
{
  unsigned short result;
  if (northeast <= west && northeast <= north)
  {
    // el valor mínimo está al noreste
    result = northeast + southeast_edge;
  }
  else if (north < west && north < northeast)
  {
    // el valor mínimo está al norte
    result = north + 1;
  }
  else
  {
    // el valor mínimo está al oeste
    result = west + 1;
  }
  return result;
}

// algoritmo 1
unsigned short algorithm_1(char *X, char *Y)
{
  unsigned short n = strlen(X) + 1;
  // construir la matriz
  Matrix m = create_matrix(n);
  // llenar la primera columna
  for (unsigned short i = 0; i < n; i++)
  {
    m[i][0] = i;
  }
  // llenar la primera fila
  for (unsigned short j = 0; j < n; j++)
  {
    m[0][j] = j;
  }
  // calcular el valor para cada casilla
  for (unsigned short i = 1; i < n; i++)
  {
    for (unsigned short j = 1; j < n; j++)
    {
      unsigned short north = m[i - 1][j];
      unsigned short west = m[i][j - 1];
      unsigned short northeast = m[i - 1][j - 1];
      unsigned short southeast_edge =
          compute_southeast_edge(X, Y, i - 1, j - 1);
      m[i][j] = compute_cell(northeast, west, north, southeast_edge);
    }
  }
  return m[n - 1][n - 1];
}

// algoritmo 2
unsigned short algorithm_2(char *X, char *Y)
{
  // se definen las variables en el stack
  unsigned short n = strlen(X) + 1;
  unsigned short row[n]; // fila en el stack
  unsigned short column[n]; // columna en el stack
  unsigned short last_west;
  unsigned short last_northeast;
  unsigned short last_north;
  for (unsigned short i = 0; i < n; i++)
  {
    row[i] = i;
    column[i] = i;
  }

  // se itera en diagonal por la matriz
  for (unsigned short k = 1; k < n; k++)
  {
    for (unsigned short i = k; i < n; i++)
    {
      if (i == k)
      {
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
      last_west = cell;
      last_northeast = row[i];
      row[i] = cell;
    }
    for (unsigned short j = k + 1; j < n; j++)
    {
      if (j - k == 1)
      {
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
      last_north = cell;
      last_northeast = column[j];
      column[j] = cell;
    }
  }
  return row[n - 1];
}

// algoritmo 3
unsigned short algorithm_3(char *p1, char *p2, unsigned short memoria)
{
  unsigned short n = strlen(p1);
  unsigned short norte, oeste, noroeste;
  unsigned short costo = 0;

  unsigned short m = memoria; // valor del largo y ancho de la submatriz
  unsigned short trozos = n / (m - 1);

  // Se crea la matriz en el heap
  Matrix matriz = create_matrix(m);
  Vector frontera_norte = create_vector(n + 1);
  Vector frontera_oeste = create_vector(n + 1);
  Vector aux_norte = create_vector(m);
  Vector aux_oeste = create_vector(m);

  // llenar frontera norte
  for (unsigned short i = 0; i < n + 1; i++)
  {
    frontera_norte[i] = i;
  }

  // llenar frontera norte
  for (unsigned short i = 0; i < n + 1; i++)
  {
    frontera_oeste[i] = i;
  }

  // llenar fila 0
  for (unsigned short i = 0; i < m; i++)
  {
    matriz[0][i] = i;
  }
  // llenar columna 0
  for (unsigned short i = 0; i < m; i++)
  {
    matriz[i][0] = i;
  }

  for (unsigned short f = 0; f < trozos; f++)
  {
    for (unsigned short c = 0; c < trozos; c++)
    {

      // construir la matriz a partir de comparar valores
      for (unsigned short i = 1; i < m; i++)
      {
        for (unsigned short j = 1; j < m; j++)
        {

          // El error tiene que estar aquí en la parte del algoritmo 1
          oeste = matriz[i - 1][j];
          norte = matriz[i][j - 1];
          noroeste = matriz[i - 1][j - 1];

          // El error tiene que estar aquí probablemente
          unsigned short letra1, letra2;
          if (f == 0)
          {
            letra1 = i - 1;
          }
          else
          {
            letra1 = (i - 2) + f * m;
          }

          if (c == 0)
          {
            letra2 = j - 1;
          }
          else
          {
            letra2 = (j - 2) + c * m;
          }

          if (p1[letra1] == p2[letra2])
          {
            costo = 0;
          }
          else
          {
            costo = 1;
          }
          matriz[i][j] = compute_cell(noroeste, oeste, norte, costo);
        }
      }

      // se llenan los valores auxiliares para utilizar después
      // llenar aux norte
      for (unsigned short i = 0; i < m; i++)
      {
        aux_norte[i] = matriz[m - 1][i];
      }

      // llenar aux oeste
      for (unsigned short i = 0; i < m; i++)
      {
        aux_oeste[i] = matriz[i][m - 1];
      }

      if (c == trozos - 1)
      {
        // llenar fila 0
        for (unsigned short i = 0; i < m; i++)
        {
          matriz[0][i] = frontera_norte[i]; // i+((c+1)*m)-1
        }
      }
      else
      {
        // llenar fila 0
        for (unsigned short i = 0; i < m; i++)
        {
          matriz[0][i] = frontera_norte[i + ((c + 1) * (m - 1))];
        }
      }

      // llenar frontera norte
      if (c == trozos - 1)
      {
        for (unsigned short i = 0; i < m; i++)
        {

          aux_oeste[i] = frontera_oeste[i + (f + 1) * (m - 1)];
        }
      }

      // llenar columna 0
      for (unsigned short i = 0; i < m; i++)
      {
        matriz[i][0] = aux_oeste[i];
      }
      
      // llenar frontera norte
      for (unsigned short i = 0; i < m; i++)
      {
        if (c == 0)
          frontera_norte[i] = aux_norte[i];
        else
          frontera_norte[i + c * (m - 1)] = aux_norte[i];
      }

      // llenar frontera norte
      if (c == trozos - 1)
      {
        for (unsigned short i = 0; i < m; i++)
        {
          aux_oeste[i] = frontera_oeste[i + f * m - 1];
        }
      }
    }
  }

  return matriz[m - 1][m - 1];
}