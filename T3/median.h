#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

void insertion_sort(unsigned long *a, int n) 
// Insertion sort array a of length n
{
  for(int j = 1; j < n; j++) {
	int key = a[j];
	// insert a[j] in the correct position a[0...(j-1)]
	int i = j - 1;
	while ((i >= 0) && (a[i] > key)) {
	  a[i + 1] = a[i];
	  i--;
	}
	a[i+1] = key;
  }
}


int partition(unsigned long *a, int n, int x)
// Partition array a of length n around x;
// Return the number of elements to the left of the pivot.
{
  // First find the pivot and place at the end
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

  // Place the pivot in the correct position
  a[n-1] = a[i];
  a[i] = x;

  return i;
}

unsigned long algorithm_1(unsigned long *a, int n, int i, int c)
// Select the ith element (indexed from 0) from the array of length n
// using the median of medians algorithm
// https://en.wikipedia.org/wiki/Median_of_medians
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