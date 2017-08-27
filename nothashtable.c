/**
 * Not Hash Table
 */

#include "nothashtable.h"

void nht_create_table(t_nht* nht) { nht->size = 0; }

int nht_search(t_nht* nht, char* key) {
  for (int i = 0; i < nht->size; i++)
    if (strcmp(nht->keys[i], key) == 0)
      return i;
  return NHT_ERROR;
}

int nht_add(t_nht* nht, char* key, size_t keylen) {
  if (nht->size == USHRT_MAX)
    return NHT_ERROR;

  nht->keys[nht->size] = (char*) malloc((keylen + 1) * sizeof(char));
  strcpy(nht->keys[nht->size], key);
  return nht->size++;
}
