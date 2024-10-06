#include <stdio.h>

#define Max 5

void printf_array(int *array) {
  printf("[%d ", array[0]);
  for (int i = 1; i < Max - 1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d]\n", array[Max-1]);
}

void insertion_sort(int *array) {
  // insertion_sort e a insercao_ordenada varias vezes
  for (int i = 1; i < Max; i++) { // O(N - 1)
    // insercao_ordenada
    for (int j = i; j > 0 && array[j] < array[j - 1]; j--) { // O(N*N/2)
      int temp = array[j - 1];
      array[j - 1] = array[j];
      array[j] = temp;
      printf("values = ");
      printf_array(array);
    }
  }
}

// O(N - 1) + O(N^2/2)
// O(N) + O(N^2)
// O(N^2)


int main() {
  int array[Max] = {5, 3, 2, 1, 4};
  printf_array(array);
  insertion_sort(array);
  printf_array(array);
  return 0;
}
