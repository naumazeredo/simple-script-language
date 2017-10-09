/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#include "parser_gen.h"
#include "lexer.h"
#include "queue.h"
#include "semantics.h"

void parse() {
  queue q;
  queue_create(&q);

  queue_push(&q, 0);
  t_token a = get_next_token();

  do {
    int u = queue_front(q);
    int p = action[u][(int)a];

    if (is_shift(p)) {
      queue_push(&q, p);
      a = get_next_token();
    } else if (is_reduction(p)) {
      int r = get_rule(p);
      queue_popn(&q, get_rule_len(r));

      u = queue_front(q);
      queue_push(&q, action[u][get_rule_left(r)]);

      semantics(r);
    } else {
      // Error
    }
  } while (queue_front(q) != 1); // final state
}
