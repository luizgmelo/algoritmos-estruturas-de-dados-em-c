#include <stdio.h>
#include <stdlib.h>

#define Max 5

void printf_array(int *arr, int start, int end) {
  printf("[%d ", arr[start]);
  for (int i = start+1; i < end; i++) {
    printf("%d ", arr[i]);
  }
  printf("%d]\n", arr[end]);
}

void merge(int *arr, int start, int middle, int end) {

  int left_size = (middle-start)+1;
  int right_size = (end-middle);

  int *left = (int*)malloc(left_size * sizeof(int));
  int *right = (int*)malloc(right_size * sizeof(int));

  // Copiando os elementos do intervalo [inicio:meio] para a sublista
  for (int x = 0; x < left_size; x++) {
    left[x] = arr[start + x];
  }

  // Copiando os elementos do intervalo [meio:fim] para a sublista
  for (int y = 0; y < right_size; y++) {
    right[y] = arr[middle + 1 + y];
  }

  int i = 0, j = 0;

  for (int k = start; k <= end; k++) {
    if (i >= left_size) {
      arr[k] = right[j];
      j++;
    }
    else if (j >= right_size) {
      arr[k] = left[i];
      i++;
    }
    else if (left[i] > right[j]) {
      arr[k] = right[j];
      j++;
    } else {
      arr[k] = left[i];
      i++;
    }
  }

  free(left);
  free(right);
}

void merge_sort(int *arr, int start, int end) {
  if (start >= end) {
    return;
  }

  int middle = (end + start) / 2;
  merge_sort(arr, start, middle);
  merge_sort(arr, middle + 1, end);
  merge(arr, start, middle, end);
}

int main() {
  int arr[Max] = {9, 8, 2, 1, 3};
  merge_sort(arr, 0, Max-1);
  printf_array(arr, 0, Max-1);
  return 0;
}
