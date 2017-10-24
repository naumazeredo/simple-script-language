/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#include "parser.h"

void parse() {
  init_tables();
  create_action_table();
  open_file();

  queue q;
  queue_create(&q);

  queue_push(&q, 0);
  t_token a = get_next_token();

  do {
    int u = queue_front(q);
    int p = action[u][(int)a];
    printf("Vai dar certo, u = %d e p = %d e a = %d!!!!!\n",u,p,(int)a);

    if (is_shift(p)) {
      queue_push(&q, p);
      a = get_next_token();
    } else if (is_reduction(p)) {
      int r = get_rule(p);
      queue_popn(&q, get_rule_len(r));

      queue_push(&q, action[u][get_rule_left(r)]);

      semantics(r);
    } else {
      // Error
    }

    u = queue_front(q);
  } while (queue_front(q) != 1); // final state
}
