#include <stdio.h>
#include <stdlib.h>
#include "time.h"

#define LIST_SIZE 10000


// Find a value in a list running element by element Complexity: O(N)
int linear_search(int *arr, int search, int size, int *attempts) {

  for (int i = 0; i < LIST_SIZE; i++) {
    if (arr[i] == search) {
      return i;
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
  
   int found = linear_search(list, search, LIST_SIZE, &attempts);
  
   if (found == -1) {
     printf("Not found!");
   } else {
     printf("Find at List[%d]=%d\n",found,list[found]);
     printf("I try %d times to assert\n",attempts);
   }
   return 0;
  }
