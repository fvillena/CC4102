// CPP program for implementation of QuickSelect
#include <bits/stdc++.h>

#include <cstdlib>
using namespace std;

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
//

// unsigned long partition2(unsigned long arr[], unsigned long l, unsigned long r) {
//   srand((unsigned)time(NULL));
//   unsigned long random_pivot = l + rand() % (r - l + 1);
//   swap(arr[r], arr[random_pivot]);
//   unsigned long x = arr[r], i = l;
//   for (unsigned long j = l; j <= r - 1; j++) {
//     if (arr[j] <= x) {
//       swap(arr[i], arr[j]);
//       i++;
//     }
//   }
//   swap(arr[i], arr[r]);
//   return i;
// }

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
  // If k is smaller than number of
  // elements in array
  if (k > 0 && k <= r - l + 1) {
    // Partition the array around last
    // element and get position of pivot
    // element in sorted array
    // unsigned long index = partition2(arr, l, r);
    unsigned long index = partition_withC(arr, l, r, c);

    // If position is same as k
    if (index - l == k - 1) return arr[index];

    // If position is more, recur
    // for left subarray
    if (index - l > k - 1) return algorithm_2(arr, l, index - 1, k, c);

    // Else recur for right subarray
    return algorithm_2(arr, index + 1, r, k - index + l - 1, c);
  }

  // If k is more than number of
  // elements in array
  return UINT_MAX;
}
