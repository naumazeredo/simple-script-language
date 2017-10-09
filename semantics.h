/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#ifndef SSL_SEMANTICS
#define SSL_SEMANTICS

#include "scope.h"

typedef struct {
  t_nonterminal type;
  union {
    struct {
      pobject obj;
    } ID;
  };
} t_attrib;

void semantics(int rule);

#endif //SSL_SEMANTICS
