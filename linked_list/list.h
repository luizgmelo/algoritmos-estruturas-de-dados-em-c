#include <stdio.h>
#include <stdlib.h>

typedef struct list List;

// funcão que cria uma lista vazia (NULL)
List *lst_create();

// função que insere um elemento no fim da lista
List *lst_insert(List *l, int v);

// função que verifica se a lista está vazia
int lst_isEmpty(List *l);

// função que imprime os elementos da lista
void lst_print(List *l);

// função que busca um elemento da lista
List *lst_search(List *l, int v);

// função que remove um elemento da lista
List *lst_remove(List *l, int v);

// função que libera memória alocada para lista
void lst_free(List *l);


