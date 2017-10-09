/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#include "scope.h"

#define MAX_NEST_LEVEL 64

pobject symbol_table[MAX_NEST_LEVEL];
int symbol_table_level = -1;

int new_block() {
  symbol_table_level++;
  symbol_table[symbol_table_level] = NULL;
  return symbol_table_level;
}

int end_block() {
  return --symbol_table_level;
}

pobject define_symbol(int name) {
  pobject obj = (pobject) malloc(sizeof(object));

  obj->name = name;
  obj->next = symbol_table[symbol_table_level];
  symbol_table[symbol_table_level] = obj;

  return obj;
}

pobject search_symbol_in_scope(int name) {
  pobject obj = symbol_table[symbol_table_level];

  while (obj != NULL) {
    if (obj->name == name)
      return obj;
    obj = obj->next;
  }

  return obj;
}

pobject search_symbol_globally(int name) {
  int i;

  for (i = symbol_table_level; i >= 0; i--) {
    pobject obj = symbol_table[symbol_table_level];

    while (obj != NULL) {
      if (obj->name == name)
        return obj;
      obj = obj->next;
    }
  }

  return obj;
}
