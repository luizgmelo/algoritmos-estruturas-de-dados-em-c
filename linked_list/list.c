#include "list.h"

struct list {
  int value;
  struct list *next;
};

int lst_isEmpty(List *l) {
  if (l == NULL) {
    return 1;
  }
  return 0;
}

List *lst_create() {
  return NULL;
}

List *lst_insert(List *l, int v) {
  List *new = (List *)malloc(sizeof(List));
  if (new == NULL) {
    printf("[ERRO] Memory allocation Failed!");
    exit(1);
  }

  new->value = v;
  new->next = NULL;

  if (l == NULL) {
    l = new;
    return l;
  }

  List *current = l;

  while(current->next != NULL) {
    current = current->next;
  }
  current->next = new;
  return l;
}

List *lst_remove(List *l, int value) {
  List *previous = NULL;
  List *current = l;

  if (l == NULL) {
    return l;
  }

  if (current->value == value) {
    l = current->next;
    free(current);
    return l;
  }

  while (current->next != NULL) {
    previous = current;
    current = current->next;

    if (current->value == value) {
      previous->next = current->next;
      free(current);
      return l;
    }
  }

  return l;
}

List *lst_search(List *l, int value) {
  List *current = l;

  while (current != NULL) {
    if (current->value == value) {
      return current;
    }
    current = current->next;
  }

  return NULL;
}

void lst_print(List *l) {
  if (lst_isEmpty(l)) {
    return;
  }
  
  List current = *l;
  printf("%d", current.value);
  while (current.next != NULL) {
    current = *(current.next);
    printf(" -> %d", current.value);
  }
  printf("\n");
}

void lst_free(List *l) {
  List *p = l;
  List *t;
  while (p != NULL) {
    t = p->next;
    free(p);
    p = t;
  }
}


int main() {
  List *list = lst_create();

  if (lst_isEmpty(list)) {
    printf("List is empty!\n");
  } else {
    printf("List is not empty!\n");
  }
  
  list = lst_insert(list, 20);
  list = lst_insert(list, 32);
  list = lst_insert(list, 22);
  list = lst_insert(list, 99);

  lst_print(list);

  if (lst_isEmpty(list)) {
    printf("List is empty!\n");
  } else {
    printf("List is not empty!\n");
  }

  list = lst_remove(list, 99);

  lst_print(list);

  List *element = lst_search(list, 22);

  if (element != NULL) {
    printf("Element %d found in the list.\n", element->value);
  } else {
    printf("Element not found in the list.\n");
  }

  lst_free(list);

  return 0;
}
