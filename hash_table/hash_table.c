#include "hash_table.h"

struct hash {
  List *buckets;
};

struct pair {
  char *k;
  int v;
};

ul djb2(char *k) {
  ul hash = 5381;
  int c;
  while ((c = *k++)) {
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  }
  return hash % NUM_BUCKETS;
}

int main() {
  return 0;
}
