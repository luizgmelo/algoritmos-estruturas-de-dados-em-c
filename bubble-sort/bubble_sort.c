#include <stdio.h>

#define Max 5

void bubble_sort(int *array) {
  for (int i = 1; i < Max; i++) {
    for (int j = 0; j < Max - 1; j++) {
      if (array[j] > array[i]) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
  }
}

void print_array(int *array) {
  printf("[%d ", array[0]);
  for (int i = 1; i < Max-1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d]\n", array[Max-1]);
}

