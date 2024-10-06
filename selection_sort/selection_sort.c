#include <stdio.h>

#define Max 7

void printf_array(int *array) {
  printf("[%d ", array[0]);
  for(int i = 1; i < Max - 1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d]\n", array[Max-1]);
}

int findSmallest(int *array) {
  int smallest = array[0];
  int smallest_index = 0;
  int ignore_latest;

  for (int i = 0; i < Max - ignore_latest; i++) {
    if (smallest > array[i]) {
      smallest = array[i];
      smallest_index = i;
   }
  }

  //Remove smallest || Shift left all elements from smallest_index until latest and ignore latest
  for (int i = smallest_index; i < Max - 1; i++) {
    array[i] = array[i + 1];
  }
  ignore_latest++;

  return smallest;
}

void selection_sort(int *array) {
  int newArray[Max];
  for (int i = 0; i < Max; i++) {
    newArray[i] = findSmallest(array);
  } 
  for (int j = 0; j < Max; j++) {
    array[j] = newArray[j];
  }
}


int main() {
  int arr[Max] = {5, 8, 1, 1, 3, 2, 6};
  selection_sort(arr); // O(N^2)
  printf_array(arr); // O(N-2)
  return 0;
}
