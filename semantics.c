/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#include "semantics.h"

#define MAX_STACK_SIZE 256

t_attrib semantic_stack[MAX_STACK_SIZE];
int semantic_stack_size = 0;

void semantic_stack_push(t_attrib attrib) {
  if (semantic_stack_size == MAX_STACK_SIZE)
    return;
  semantic_stack[semantic_stack_size++] = attrib;
}

void semantic_stack_pop (int n) {
  if (semantic_stack_size == 0)
    return;
  semantic_stack_size--;
}

t_attrib semantic_stack_top () {
  if (semantic_stack_size == 0)
    return (t_attrib){}; // Error
  return semantic_stack[semantic_stack_size-1];
}

void semantics(int rule) {
  // TODO
}
