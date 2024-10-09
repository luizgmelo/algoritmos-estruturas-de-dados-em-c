#include <stdio.h>
#include <stdlib.h>

#define NUM_BUCKETS 10

typedef struct hash Hash;
typedef unsigned long ul;
typedef struct pair KeyValuePair;

// Create a hash table
Hash *hst_create();

// Calculate hash djb2 algorithm
ul djb2(char *k);

// Insert a key-value pair in hash table
Hash *hst_insert(Hash *h, char *k, int v);

// Search a value in hash table
int hst_search(Hash *h, char *k);

// Remove a key-value pair in hash table;
void hst_remove(Hash *h, char *k);

// Free memory of hash table
void hst_frre(Hash *h);

