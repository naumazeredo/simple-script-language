/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#ifndef SSL_QUEUE
#define SSL_QUEUE

typedef struct {
  int cap, size, begin;
  int* data;
} queue;

void queue_create  (queue* q);
void queue_push    (queue* q, int v);
int  queue_pop     (queue* q);
void queue_popn    (queue* q, int n);
int  queue_front   (queue q);
int  queue_is_empty(queue q);

#endif //SSL_QUEUE
