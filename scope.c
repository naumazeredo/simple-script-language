/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#include "scope.h"

#define MAX_NEST_LEVEL 64

object int_        = { -1, NULL, KIND_SCALAR_TYPE};
pobject pInt       = &int_;

object char_       = { -1, NULL, KIND_SCALAR_TYPE};
pobject pChar      = &char_;

object bool_       = { -1, NULL, KIND_SCALAR_TYPE};
pobject pBool      = &bool_;

object string_     = { -1, NULL, KIND_SCALAR_TYPE};
pobject pString    = &string_;

object universal_  = { -1, NULL, KIND_SCALAR_TYPE};
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
  pobject obj;

  for (i = symbol_table_level; i >= 0; i--) {
    obj = symbol_table[symbol_table_level];

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
      return check_types(t1->Alias.pBaseType, t2->Alias.pBaseType);
    } else if (t1->kind == KIND_ARRAY_TYPE) {
      if (t1->Array.nNumElems == t2->Array.nNumElems) {
        return check_types(t1->Array.pElemType, t2->Array.pElemType);
      }
    } else if (t1->kind == KIND_STRUCT_TYPE) {
      pobject f1 = t1->Struct.pFields;
      pobject f2 = t2->Struct.pFields;
      while (f1 != NULL && f2 != NULL) {
        if (!check_types(f1->Field.pType, f2->Field.pType))
          return 0;
      }
      return (f1 == NULL && f2 == NULL);
    }
  }
  return 0;
}
