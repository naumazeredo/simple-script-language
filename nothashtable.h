/**
 * Not Hash Table
 *
 * @brief: Not a hash table. Just a simple table.
 * @author: Naum Azeredo Fernandes Barreira
 *
 */

#ifndef SSC_NOTHASHTABLE
#define SSC_NOTHASHTABLE

#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define NHT_MAX_SIZE USHRT_MAX
#define NHT_ERROR -1

typedef struct {
  int   size;
  char* keys[NHT_MAX_SIZE];
} t_nht;

void nht_create_table(t_nht* nht);
int  nht_search(t_nht* nht, char* key);
int  nht_add(t_nht* nht, char* key, size_t keylen);

#endif //SSC_NOTHASHTABLE
