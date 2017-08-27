/**
 *
 */

#include <stdio.h>

#include "lexer.h"


const char* tts[TOKEN_NUM] = {
  "TOKEN_TRUE", "TOKEN_FALSE",
  "TOKEN_CHAR", "TOKEN_INTEGER", "TOKEN_BOOLEAN", "TOKEN_ARRAY",
  "TOKEN_FUNCTION", "TOKEN_STRING", "TOKEN_VAR", "TOKEN_STRUCT",
  "TOKER_RETURN", "TOKEN_BREAK", "TOKEN_CONTINUE",
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

int main() {
  init_tables();

  do {
    getNextToken();
    printf("%s", tts[token]);
    if (token == TOKEN_ID) printf(" %s (%d)", table_ids.keys[secondary_token], secondary_token);

    if (token == TOKEN_STRINGVAL) printf(" %s (%d)", getStringConst(secondary_token), secondary_token);
    if (token == TOKEN_NUMERAL)   printf(" %d (%d)", getNumeralConst(secondary_token), secondary_token);
    if (token == TOKEN_CHARACTER) printf(" %c (%d)", getCharConst(secondary_token), secondary_token);

    printf("\n");
  } while (token != TOKEN_UNKNOWN && token != TOKEN_EOF);

  return 0;
}
