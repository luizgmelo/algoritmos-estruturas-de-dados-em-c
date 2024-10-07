#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Max 3

typedef struct Stack {
  int *data;
  int top;
} Stack;

Stack createStack() {
  Stack stack;
  stack.data = (int*)malloc(Max*sizeof(int));
  if (stack.data == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
  }
  stack.top = -1;
  return stack;
}

bool isEmpty(Stack *stack) {
  if (stack->top == -1) {
    printf("Stack is empty!\n");
    return true; }
  return false;
}

bool isFull(Stack *stack) {
  if (stack->top == Max - 1) {
    printf("Stack is full!\n");
    return true;
  }
  return false;
}

void push(Stack *stack, int data) {
  if (isFull(stack)) {
    printf("You can not push the data\n");
    return;
  }

  stack->top++;
  stack->data[stack->top] = data;
}

int pop(Stack *stack) {
  if (isEmpty(stack)) {
    printf("You can not pop in the stack\n");
    return -1;
  }
  int removed = stack->data[stack->top];
  stack->top--;
  return removed;
}

int peek(Stack *stack) {
  if (isEmpty(stack)) {
    return -1;
  }

  return stack->data[stack->top];
}

void printf_stack(Stack *stack) {
  printf("----start----\n");
  for (int i = stack->top; i >= 0; i--) {
    printf("    |%d|    \n", stack->data[i]);
  }
  printf("----end----\n");
}

int main() {
  Stack stack;
  stack = createStack();
  
  printf("%d\n",isEmpty(&stack));
  push(&stack, 2);
  push(&stack, 7);
  pop(&stack);
  printf_stack(&stack);
  pop(&stack);
  push(&stack, 9);
  push(&stack, 3);
  push(&stack, 5);
  printf_stack(&stack);
  printf("%d\n",isFull(&stack));

  printf("Peek: %d\n",peek(&stack));
  printf("Pop: %d\n",pop(&stack)); //Pop(5)

  printf_stack(&stack);

  // Edge cases
  pop(&stack); //Pop(3)
  printf_stack(&stack);
  pop(&stack); //Pop(9)
  pop(&stack);

  push(&stack, 6);
  push(&stack, 8);
  push(&stack, 10);
  push(&stack, 22); // Is Full!

  free(stack.data);
  return 0;
}
