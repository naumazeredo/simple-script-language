/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#ifndef SSL_STACK
#define SSL_STACK

typedef struct {
  int cap, size;
  int* data;
} stack;

void stack_print   (stack s);
void stack_create  (stack* s);
void stack_push    (stack* s, int v);
int  stack_pop     (stack* s);
void stack_popn    (stack* s, int n);
int  stack_top     (stack s);
int  stack_is_empty(stack s);

#endif //SSL_STACK
