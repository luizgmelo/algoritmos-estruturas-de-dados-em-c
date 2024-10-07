#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Max 5

typedef struct Queue {
  int* data;
  int front;
  int rear;
  int size;
  int capacity;
} Queue;

Queue createQueue() {
  Queue queue;
  queue.data = (int*)malloc(Max*sizeof(int));
  queue.front = 0;
  queue.rear = 0;
  queue.size = 0;
  queue.capacity = Max;
  return queue;
}

bool isEmpty(Queue *queue) {
  if (queue->size == 0) {
    printf("Queue is empty!\n");
    return true;
  }
  return false;
}

void printf_queue(Queue queue) {
  if (isEmpty(&queue))  
  {
    printf("[]\n");
    return;
  }
  printf("[%d", queue.data[queue.front]);
  for (int i = queue.front+1; i < queue.rear; i++) {
    printf(" %d", queue.data[i]);
  }
  printf("]\n");
}

bool isFull(Queue *queue) {
  if (queue->size == queue->capacity) {
    printf("Queue is full!\n");
    return true;
  }
  return false;
}


void enqueue(Queue *queue, int data) {
  if (isFull(queue)) {
    return;
  }

  queue->data[queue->rear] = data;
  queue->rear++;
  queue->size++;
}


void dequeue(Queue *queue) {
  if (isEmpty(queue)) {
    queue->front = 0;
    queue->rear = 0;
    return;
  }

  queue->front++;
  queue->size--;
  
  if (isEmpty(queue)) {
    queue->front = 0;
    queue->rear = 0;
  }
}

int peek(Queue *queue) {
  if (isEmpty(queue)) {
    return -1;
  }
  return queue->data[queue->front];
}

int main() {
  Queue queue = createQueue();
  enqueue(&queue, 10); // [10]
  enqueue(&queue, 4);  // [10, 4]
  dequeue(&queue); // [4]
  enqueue(&queue, 2); // [4, 2]
  dequeue(&queue); // [2]
  enqueue(&queue, 2); // [2,2]
  enqueue(&queue, 3); // [2,2,3]
  enqueue(&queue, 6); // [2,2,3,6]
  dequeue(&queue); // [2,3,6]

  printf_queue(queue);

  // Using Peek
  printf("Peek: %d\n", peek(&queue));

  free(queue.data);
  return 0;
}
