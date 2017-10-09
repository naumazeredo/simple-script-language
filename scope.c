/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#include "scope.h"

#define MAX_NEST_LEVEL 64

object int_        = { -1, NULL, SCALAR_TYPE_ };
pobject pInt       = &int_;

object char_       = { -1, NULL, SCALAR_TYPE_ };
pobject pChar      = &char_;

object bool_       = { -1, NULL, SCALAR_TYPE_ };
pobject pBool      = &bool_;

object string_     = { -1, NULL, SCALAR_TYPE_ };
pobject pString    = &string_;

object universal_  = { -1, NULL, SCALAR_TYPE_ };
pobject pUniversal = &universal_;


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

int check_types(pobject t1, pobject t2)
{
  /**/ if (t1 == t2) return 1;
  else if (t1 == pUniversal || t2 == pUniversal) return 1;
  else if (t1->kind == KIND_UNIVERSAL || t2->kind == KIND_UNIVERSAL) return 1;
  else if (t1->kind == t2->kind) {
    if (t1->kind == KIND_ALIAS_TYPE) {
      return check_types(t1->Alias.base_type, t2->Alias.base_type);
    } else if (t1->kind == KIND_ARRAY_TYPE) {
      if (t1->Array.num_elems == t2->Array.num_elems) {
        return check_types(t1->Array.elem_type, t2->Array.elem_type);
      }
    } else if (t1->kind == KIND_STRUCT_TYPE) {
      pobject f1 = t1->Struct.fields;
      pobject f2 = t2->Struct.fields;
      while (f1 != NULL && f2 != NULL) {
        if (!check_types(f1->Field.type, f2->Field.type))
          return 0;
      }
      return (f1 == NULL && f2 == NULL);
    }
  }
  return 0;
}
