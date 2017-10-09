/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#ifndef SSL_SCOPE
#define SSL_SCOPE

#include "parser_gen.h"

#define MAX_NEST_LEVEL 64

typedef enum {
  KIND_UNDEFINED = -1, KIND_VAR, KIND_PARAM, KIND_FUNCTION, KIND_FIELD,
  KIND_ARRAY_TYPE, KIND_STRUCT_TYPE, KIND_ALIAS_TYPE, KIND_SCALAR_TYPE,
  KIND_UNIVERSAL
} t_kind;

typedef struct object {
  int name;
  struct object* next;

  t_kind kind;

  union {
    struct {
      struct object* type;
      int nIndex;
      int nSize;
    } Var, Param, Field;

    struct {
      struct object* ret_type;
      struct object* params;
      int nIndex;
    } Function;

    struct {
      struct object* elem_type;
      int nNumElems;
      int nSize;
    } Array;

    struct {
      struct object* fields;
      int nSize;
    } Struct;

    struct {
      struct object* base_type;
      int nSize;
    } Alias;
  };
} object, * pobject;

extern pobject symbol_table[MAX_NEST_LEVEL];
extern int symbol_table_level;

int new_block();
int end_block();

pobject define_symbol(int name);
pobject search_symbol_in_scope(int name);
pobject search_symbol_globally(int name);

#endif //SSL_SCOPE
