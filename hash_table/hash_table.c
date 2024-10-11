#include "hash_table.h"

typedef struct entry_t {
  char *pKey;
  int value;
  struct entry_t *next;
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
  entry->pKey = malloc(strlen(pKey)+1);

  // set key and value
  strcpy(entry->pKey, pKey);
  entry->value = value;

  // next start out null but may be set later on
  entry->next = NULL;

  return entry;
}

void ht_set(ht_t *ht, char *pKey, int value) {
  ul hash = djb2(pKey);

  entry_t *entry = ht->pEntries[hash];
 
  if (entry == NULL) {
    ht->pEntries[hash] = ht_pair(pKey, value);
    return;
  }

  entry_t *prev = entry;

  while (entry != NULL) {
    if (strcmp(entry->pKey, pKey) == 0) {
      // Match found
      entry->value = value;
      return;
    }

    prev = entry;
    entry = entry->next;
  }

  prev->next = ht_pair(pKey, value);
}

int ht_get(ht_t *ht, char *pKey) {
  ul hash = djb2(pKey);

  entry_t *entry = ht->pEntries[hash];

  if (entry == NULL) {
    return -1;
  }

  while (entry != NULL) {
    if (strcmp(entry->pKey, pKey) == 0) {
      return entry->value;
    }

    entry = entry->next;
  }

  return -1;
}

void ht_del(ht_t *ht, char *pKey) {
  ul hash = djb2(pKey);

  entry_t *entry = ht->pEntries[hash];

  if (entry == NULL) {
    return;
  }

  entry_t *prev = entry;
  int idx = 0;

  while (entry != NULL) {
    if (strcmp(entry->pKey, pKey) == 0) {
      // first item and next is null
      if (entry->next == NULL && idx == 0) {
        ht->pEntries[hash] = NULL;
      }

      // first item and next is not null
      if (entry->next != NULL && idx == 0) {
        ht->pEntries[hash] = entry->next;
      }
      
      // last item
      if (entry->next == NULL && idx != 0) {
        prev->next = NULL;
      }

      // middle item
      if (entry->next != NULL && idx != 0) {
        prev->next = entry->next;
      }
      
      free(entry->pKey);
      free(entry);

      return;
    }
  }

  prev = entry;
  entry = entry->next;
  idx++;
}

  }
}

int main() {
  ht_t *ht = ht_create();

  ht_set(ht, "guilherme", 19);
  ht_set(ht, "luiz", 12);
  ht_set(ht, "roberto", 92);

  // update "guilherme"
  ht_set(ht, "guilherme", 48);

  ht_set(ht, "fabricio", 53);
  ht_set(ht, "luana", 17);
  ht_set(ht, "jaqueline", 29);

  printf("HASH: %lu\n", djb2("jaqueline"));

  // get "guilherme", "luiz", "roberto"
  printf("ht['guilherme']=%d\n", ht_get(ht, "guilherme"));
  printf("ht['luiz']=%d\n", ht_get(ht, "luiz"));
  printf("ht['roberto']=%d\n", ht_get(ht, "roberto"));

  // remove "luiz", "roberto"
  ht_del(ht, "luiz");
  ht_del(ht, "roberto");

  printf("ht['luiz']= %d\n", ht_get(ht, "luiz")); // -1
  printf("ht['roberto']= %d\n", ht_get(ht, "roberto")); // -1

  return 0;
}
