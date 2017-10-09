/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#include "queue.h"

#include <stdlib.h>

void queue_create(queue* q) {
  q->cap = 1;
  q->size = 0;
  q->begin = 0;
  q->data = (int*)malloc(sizeof(int));
}

void queue_push(queue* q, int v) {
  if (q->cap == q->size) {
    q->cap *= 2;
    q->data = (int*)realloc(q->data, q->cap * sizeof(int));

    int i;
    for (i = 0; i < q->begin; i++)
      q->data[q->begin + q->size + i] = q->data[i];
  }

  int end = (q->begin + q->size) % q->cap;
  q->data[end] = v;
  q->size++;
}

int queue_pop(queue* q) {
  if (q->size == 0)
    return -1;

  if (q->size < q->cap / 4) {
    for (int i = q->size-1; i >= 0; i--)
      q->data[i] = q->data[(q->begin + i) % q->cap];

    q->cap /= 2;
    q->data = (int*)realloc(q->data, q->cap * sizeof(int));
  }

  return q->data[q->begin];
  q->begin++;
  q->size--;
}

void queue_popn(queue* q, int n) {
  if (n <= 0) return;
  for (int i = 0; i < n; i++)
    queue_pop(q);
}

int queue_front(queue q) {
  if (q.size == 0)
    return -1;

  return q.data[q.size-1];
}

int queue_is_empty(queue q) {
  return q.size == 0;
}
