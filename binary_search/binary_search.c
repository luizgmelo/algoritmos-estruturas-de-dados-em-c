#include "stdio.h"
#include "stdlib.h" // srand() and rand();
#include "time.h" // time()

#define LIST_SIZE 100000


// Find a value in order list Complexity: O(LOG N)
int binary_search(int *arr, int value, int size, int *attempts) {
  int start = 0;
  int end = size - 1;

  while (start <= end) {

    int middle = (end + start) / 2;
    printf("%d %d\n",arr[middle], value);

    if (arr[middle] == value) {
      return middle;
    } else if (arr[middle] > value) {
      end = middle - 1;
    } else {
      start = middle + 1;
    }
    *attempts = *attempts + 1;
  }

  return -1;
}


int main() {
  int list[LIST_SIZE];
  int search;
  int attempts = 0;

  srand(time(NULL));
  
  for (int i = 0; i < LIST_SIZE; i++) {
    list[i] = i + 1;
  }
  
  // Value to find
  search = rand()%LIST_SIZE;

  int found = binary_search(list, search, LIST_SIZE, &attempts);

  if (found == -1) {
    printf("Not found!");
  } else {
    printf("Find at List[%d]=%d\n",found,list[found]);
    printf("I try %d times to assert\n",attempts);
  }
  return 0;
}
