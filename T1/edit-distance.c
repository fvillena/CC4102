#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int **Matrix;

Matrix create_matrix(int n)
{
    int **rows = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        rows[i] = malloc(n * sizeof(int));
    }
    return rows;
}

typedef int *Vector;

Vector create_vector(int n)
{
    int *vector = malloc(n * sizeof(int *));
    return vector;
}

void print_matrix(Matrix m, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

int compute_southeast_edge(char* X, char* Y, int i, int j)
{
    char x = X[i];
    char y = Y[j];
    // printf("%c%c ", x, y);
    if (x == y)
    {
        return 0;
    }
    else
    {
        return 1;
    }    
}

int dynamic_programming_algorithm(char *X, char *Y)
{
    int n = strlen(X) + 1;
    // construir la matriz
    Matrix m = create_matrix(n);
    // llenar la primera columna
    for (int i = 0; i < n; i++)
    {
        m[i][0] = i;
    }
    // llenar la primera fila
    for (int j = 0; j < n; j++)
    {
        m[0][j] = j;
    }
    // calcular el valor para cada casilla
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            int north = m[i-1][j];
            int west = m[i][j-1];
            int northeast = m[i-1][j-1];
            int southeast_edge = compute_southeast_edge(X, Y, i-1, j-1);
            // printf("%d%d ", up, left);
            if (northeast <= west && northeast <= north)
            {
                // el valor mínimo está al noreste
                m[i][j] = northeast + southeast_edge;
            }
            else if (north < west && north < northeast)
            {
                // el valor mínimo está al norte
                m[i][j] = north + 1;
            }
            else
            {
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
    return m[n-1][n-1];
}
int in_cache_algorithm(char *X, char *Y)
{
    int n = strlen(X) + 1;
    Vector row = create_vector(n);
    Vector column = create_vector(n);
    for (int i = 0; i < n; i++)
    {
        row[i] = i;
        column[i] = i;
        // printf("%d %d\n", row[i], column[i]);
    }
    Vector current_row = create_vector(n-1);
    for (int i = 0; i < n-1; i++)
    {
        
    }
    return 1;
}
void main()
{
    char S[] = "banana";
    char T[] = "ananas";
    int edit_distance = dynamic_programming_algorithm(&S, &T);
    // int edit_distance = in_cache_algorithm(&S, &T);
    printf("%d\n",edit_distance);
}