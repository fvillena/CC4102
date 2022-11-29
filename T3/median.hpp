/*
El código utilizado se basó en las siguientes fuentes:
- https://www.delftstack.com/es/howto/cpp/shuffle-vector-cpp/
- https://github.com/jjh42/algo/blob/master/median.c
- https://www.geeksforgeeks.org/quickselect-algorithm/
- https://en.wikipedia.org/wiki/Median_of_medians
*/

#include <math.h>
#include <algorithm>
#include <limits.h>
#include <time.h>
#include <vector>
using namespace std;

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

void insertion_sort(unsigned long *a, int n) 
// Se ordena el arreglo a de largo n con insertion sort
{
  for(int j = 1; j < n; j++) {
	int key = a[j];
  // se inserta a[j] en la posición correcta a[0...(j-1)]
	int i = j - 1;
	while ((i >= 0) && (a[i] > key)) {
	  a[i + 1] = a[i];
	  i--;
	}
	a[i+1] = key;
  }
}


int partition(unsigned long *a, int n, int x)
// Se particiona un arreglo a de largo n alrededor de x;
// Retorna el número de elmentos a la izquierda del pivote
{
  // Primero encuentra el pivote y lo pone al final
  for(int i = 0; i < n; i++) {
	if(a[i] == x) {
	  a[i] = a[n-1];
	  a[n-1] = x;
    }
  }

  int i = 0;
  for(int j = 0; j < (n-1); j++) {
	if(a[j] <= x) {
	  int tmp = a[j];
	  a[j] = a[i];
	  a[i] = tmp;
	  i++;
	}
  }

  // Pone el pivote en la posición correcta
  a[n-1] = a[i];
  a[i] = x;

  return i;
}

unsigned long algorithm_1(unsigned long *a, int n, int i, int c)
// Selecciona el elemento i desde el arreglo de largo n usando mediana
// de medianas, particionando el arreglo en subarreglos de tamaño c
{
  if(n == 1) {
	return a[0];
  }

  int n_meds = 0;
  for(int i = 0; i < n; i += c) {
	int l = min(c, n - i);
	insertion_sort(a + i, l);
	int tmp = a[i/c];
	a[i/c] = a[i + l/2];
	a[i + l/2] = tmp;
	n_meds++;
  }

  unsigned long median_of_medians;
  if(n_meds > 1) {
    median_of_medians = algorithm_1(a, n_meds/2, n_meds, c);
  }
  else {
	median_of_medians = a[0];
  }

  int k = partition(a, n, median_of_medians);

  if(k == i) {
	return median_of_medians;
  }
  else if (i < k) {
	return algorithm_1(a, i, k, c);
  }
  else {
	return algorithm_1(a + k, i - k, n - k, c);
  }
}

int c_Calculator(double error, double tolerancia){
    int c = 7*(4/pow(tolerancia, 2))*log(2/error); // Tamaño arreglo auxiliar en funcion del error y tolerancia
    return c;
}

template<typename T>
unsigned long algorithm_3(int c, vector<T> &A){

    unsigned long Aux[c];                  // Arreglo auxilaiar

    unsigned long num;
    srand(time(NULL));
    

    unsigned long fin = A.size();
    
    for(int j = 0; j<c; j++){
        num = rand() % fin;
        Aux[j] = A[num];
        A[num] = A[fin];
        fin--;
    }


    sort(Aux, Aux + c);

    return Aux[(c/2)]; 
}



// obtiene c elementos de manera aleatoria del arreglo arr
// obtiene la mediana dentro de esos c elementos
// retorna el indice de dicha mediana dentro del arreglo arr
unsigned long get_medianC(unsigned long arr[], unsigned long c, unsigned long l, unsigned long r) {
  srand((unsigned)time(NULL));
  vector<unsigned long> vc(c);
  vector<pair<unsigned long, unsigned long>> vreal(c);

  for (unsigned long i = 0; i < c; i++) {
    vc[i] = l + rand() % (r - l + 1);
  }
  for (unsigned long i = 0; i < c; i++) {
    vreal[i] = make_pair(arr[vc[i]], vc[i]);
  }
  sort(vreal.begin(), vreal.end());
  return vreal[ceil(c / 2)].second;
}

// genera 2 particiones entorno a un pivote seleccionado de manera "aleatoria"
// Hace lo mismo que partition pero obtiene los pivotes de la siguiente manera:
// selecciona c elementos del arreglo arr de forma aleatoria, obtiene la mediana
// dentro de esos c elementos ocupa dicha mediana como pivote
unsigned long partition_withC(unsigned long arr[], unsigned long l, unsigned long r, unsigned long c) {
  srand((unsigned)time(NULL));
  unsigned long random_pivot = get_medianC(arr, c, l, r);
  swap(arr[r], arr[random_pivot]);
  unsigned long x = arr[r], i = l;
  for (unsigned long j = l; j <= r - 1; j++) {
    if (arr[j] <= x) {
      swap(arr[i], arr[j]);
      i++;
    }
  }
  swap(arr[i], arr[r]);
  return i;
}

unsigned long algorithm_2(unsigned long *arr, unsigned long l, unsigned long r, unsigned long k, unsigned long c) {
  // Si k es menor que el numero de elementos en el arreglo
  if (k > 0 && k <= r - l + 1) {
    // Particiona el arreglo alrededor del último elemento
    // y saca la posición del pivote en un arreglo ordenado
    unsigned long index = partition_withC(arr, l, r, c);

    // Si la posición es igual a k
    if (index - l == k - 1) return arr[index];

    // si la posición es mayor, llamar recursivamente sobre el arreglo izquierdo
    if (index - l > k - 1) return algorithm_2(arr, l, index - 1, k, c);

    // Si no llamar recursivamente a la derecha
    return algorithm_2(arr, index + 1, r, k - index + l - 1, c);
  }
  
  // si k es mayor a al cantidad de elementos del arreglo
  return UINT_MAX;
}
