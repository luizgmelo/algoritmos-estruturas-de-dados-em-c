#include "hash_table.h"
#include <cstdio>
#include <cstring>

typedef struct entry_t {
  char *pKey;
  int value;
  struct list *next;
} entry_t;

typedef struct {
  struct entry_t **pEntries;
} ht_t;

ht_t *ht_create(void) {
  // allocate table
  ht_t *hashtable = malloc(sizeof(ht_t) * 1);
  
  // allocate table entries
  hashtable->pEntries = malloc(sizeof(entry_t) * TABLE_SIZE);

  for (int i = 0; i < TABLE_SIZE; i++) {
    hashtable->pEntries[i] = NULL;
  }

  return hashtable;
}

ul djb2(char *k) {
  ul hash = 5381;
  int c;
  while ((c = *k++)) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash % TABLE_SIZE;
}

entry_t *ht_pair(char *pKey, int value) {
  // allocate entry
  entry_t *entry = malloc(sizeof(entry_t)*1);
  entry->pKey = malloc(strlen(key)+1);
  entry->value = value;

  // not finished
}

void ht_set(ht_t *ht, char *pKey, int value) {
  ul hash = djb2(pKey);

  entry_t *entry = ht->pEntries[hash];
 
  if (entry == NULL) {
    ht->pEntries[hash] = ht_pair(pKey, value);
  }
}

int main() {
  ht_t *ht = ht_create();
  return 0;
}
