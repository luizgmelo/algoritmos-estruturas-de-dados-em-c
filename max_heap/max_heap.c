#include <stdio.h>
// Max-Heap: The parent node is always greater than or equal to its child nodes.

#define LIST_SIZE 10

int left(int i) {
  return 2 * i + 1;
}

int right(int i) {
  return 2 * i + 2;
}

int parent(int i) {
  return (i - 1) / 2;
}

void swap(int arr[], int a, int b) {
  int temp = arr[a]; arr[a] = arr[b];
  arr[b] = temp;
}

int hp_insert(int heap[], int key, int *size) {

  if (*size == LIST_SIZE ) {
    // Is full
    printf("Heap is full!\n");
    return 0;
  }

  // Add element at the end of heap
  int i = *size;
  heap[i] = key;
  *size = *size + 1;

  // Heapify
  while (i >= 0 && heap[i] > heap[parent(i)]) {
    swap(heap, i, parent(i));
    i = parent(i);
  }

  return 1;
}

int getMax(int heap[], int size) {
  if (size <= 0) {
    printf("Heap is empty!\n");
    return -1;
  }
  return heap[0];
}

int extract_max(int heap[], int *size) {
  if (*size <= 0) {
    printf("Heap is empty!\n");
    return -1;
  }

  int extract = heap[0];
  heap[0] = heap[*size-1];  
  (*size)--;

  int j = 0;
  
  // Heapify Down
  while (1) {
    int max = j;
    int leftIndex = left(j);
    int rightIndex = right(j);

    if (leftIndex < *size && heap[leftIndex] > heap[max]) {
      max = leftIndex;
    }

    if (rightIndex < *size && heap[rightIndex] > heap[max]) {
      max = rightIndex;
    }

    if (max == j) {
      break;
    }

    swap(heap, j, max);
    j = max;
  }

  return extract;
}



int main() {
  int heap[LIST_SIZE];
  int size = 0;

  hp_insert(heap, 3, &size);
  hp_insert(heap, 20, &size);
  hp_insert(heap, 7, &size);
  hp_insert(heap, 12, &size);
  hp_insert(heap, 18, &size);

  printf("Extract max: %d\n", extract_max(heap, &size));
  printf("Extract max: %d\n", extract_max(heap, &size));
  printf("Extract max: %d\n", extract_max(heap, &size));
  printf("Extract max: %d\n", extract_max(heap, &size));
  printf("Extract max: %d\n", extract_max(heap, &size));
  printf("Extract max: %d\n", extract_max(heap, &size));
  printf("Max/Root: %d\n", getMax(heap, size));

  return 0;
}
