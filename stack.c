/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

void stack_print(stack s) {
  printf("stack: ");
  for (int i = 0; i < s.size; i++)
    printf("%d ", s.data[i]);
  printf("\n");
}

void stack_create(stack* s) {
  s->cap = 1;
  s->size = 0;
  s->data = (int*)malloc(sizeof(int));
}

void stack_push(stack* s, int v) {
  if (s->cap == s->size) {
    s->cap *= 2;
    s->data = (int*)realloc(s->data, s->cap * sizeof(int));
  }

  s->data[s->size] = v;
  s->size++;
}

int stack_pop(stack* s) {
  if (s->size == 0)
    return -1;

  if (s->size < s->cap / 4) {
    s->cap /= 2;
    s->data = (int*)realloc(s->data, s->cap * sizeof(int));
  }

  int v = s->data[s->size];
  s->size--;

  return v;
}

void stack_popn(stack* s, int n) {
  if (n <= 0) return;
  for (int i = 0; i < n; i++)
    stack_pop(s);
}

int stack_top(stack s) {
  if (s.size == 0)
    return -1;

  return s.data[s.size-1];
}

int stack_is_empty(stack s) {
  return s.size == 0;
}
