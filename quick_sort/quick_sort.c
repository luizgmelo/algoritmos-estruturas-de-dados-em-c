#include <stdio.h>

#define Max 5

void printf_array(int *array) {
  printf("[%d ", array[0]);
  for (int i = 1; i < Max - 1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d]\n", array[Max-1]);
}

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int *arr, int start, int end) {
  int pivot = arr[start];
  int i = start + 1;

  for (int j = start + 1; j <= end; j++) {
    if (arr[j] <= pivot) {
      swap(&arr[i], &arr[j]);
      i++;
    }
  }

  swap(&arr[start], &arr[i - 1]);

  return i - 1;
}

void quick_sort(int *arr, int start, int end) {
  if (start < end) {
    int pivot = partition(arr, start, end);

    quick_sort(arr, start, pivot - 1);
    quick_sort(arr, pivot + 1, end);
  }
}


int main() {
  int arr[Max] = {3, 1, 2, 5, 4};
  int duplicated[Max] = {3, 3, 3, 3, 3};
  int ordenated[Max] = {1, 2, 3, 4, 5};
  int inverted[Max] = {5, 4, 3, 2, 1};
  quick_sort(arr, 0, Max-1);
  quick_sort(duplicated, 0, Max-1);
  quick_sort(ordenated, 0, Max-1);
  quick_sort(inverted, 0, Max-1);
  printf("Unorded: ");
  printf_array(arr);
  printf("Duplicated: ");
  printf_array(duplicated);
  printf("Ordenated: ");
  printf_array(ordenated);
  printf("Inverted: ");
  printf_array(inverted);
  return 0;
}
