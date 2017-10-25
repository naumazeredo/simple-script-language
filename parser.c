/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#include "parser.h"

char* token_name[] = {
  "TOKEN_TRUE", "TOKEN_FALSE",
  "TOKEN_CHAR", "TOKEN_INTEGER", "TOKEN_BOOLEAN", "TOKEN_ARRAY",
  "TOKEN_FUNCTION", "TOKEN_STRING", "TOKEN_VAR", "TOKEN_STRUCT",
  "TOKEN_RETURN", "TOKEN_BREAK", "TOKEN_CONTINUE",
  "TOKEN_WHILE", "TOKEN_DO", "TOKEN_IF", "TOKEN_ELSE",
  "TOKEN_TYPE", "TOKEN_OF",
  "TOKEN_EOF",
  "TOKEN_COLON", "TOKEN_SEMICOLON", "TOKEN_COMMA",
  "TOKEN_EQUAL",
  "TOKEN_LEFT_SQUARE", "TOKEN_RIGHT_SQUARE", "TOKEN_LEFT_BRACES", "TOKEN_RIGHT_BRACES",
  "TOKEN_LEFT_PARENTHESIS", "TOKEN_RIGHT_PARENTHESIS",
  "TOKEN_AND", "TOKEN_OR",
  "TOKEN_LESS", "TOKEN_GREATER", "TOKEN_LESS_OR_EQUAL", "TOKEN_GREATER_OR_EQUAL",
  "TOKEN_NOT_EQUAL", "TOKEN_EQUAL_EQUAL",
  "TOKEN_PLUS", "TOKEN_MINUS", "TOKEN_TIMES", "TOKEN_DIVIDE",
  "TOKEN_PLUS_PLUS", "TOKEN_MINUS_MINUS",
  "TOKEN_DOT", "TOKEN_NOT",
  "TOKEN_CHARACTER", "TOKEN_NUMERAL", "TOKEN_STRINGVAL", "TOKEN_ID",
  "TOKEN_UNKNOWN"
};

void parse() {
  init_tables();
  create_action_table();
  open_file();

  stack s;
  stack_create(&s);

  stack_push(&s, 0);
  t_token a = get_next_token();

  do {
    int u = stack_top(s);
    int p = action[u][(int)a];
    //stack_print(s);

    if (is_shift(p)) {
      stack_push(&s, p);
      a = get_next_token();
    } else if (is_reduction(p)) {
      int r = get_rule(p);
      stack_popn(&s, get_rule_len(r));

      u = stack_top(s);

      stack_push(&s, action[u][get_rule_left(r)]);

      semantics(r);
    } else {
      // Error
    }

    u = stack_top(s);
  } while (stack_top(s) != 1 || a != TOKEN_EOF); // final state

  close_file();
}
