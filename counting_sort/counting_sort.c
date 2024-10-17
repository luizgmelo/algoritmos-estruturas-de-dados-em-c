#include <stdio.h>

#define Max 10 // nums in range 0-100

void counting_sort(int* array, int size) {
  int counter[size];

  for (int x = 0; x < Max; x++) {
    counter[x] = -1;
  }

  for (int i = 0; i < Max; i++) {
    int n = array[i];
    if (counter[n] == -1) {
      counter[n] = 1;
    } else {
      counter[n]++;
    }
  }
  
  int y = 0;
  for (int j = 0; j < Max; j++) {
    if (counter[j] == -1) {
      continue;
    }
    while (counter[j] > 0) {
      array[y] = j;
      y++;
      counter[j]--;
    }
  }
}

void printf_array(int* array) {
  printf("[%d ", array[0]);
  for (int i = 1; i < Max - 1; i++) {
    printf("%d ", array[i]);
  }
  printf("%d]", array[Max-1]);
}

int main() {
  int array[Max] = {4,3,7,8,6,6,9,6,4,7};
  counting_sort(array, Max);
  printf_array(array);
  return 0;
}
