/**
 *  Simple Scripting Language
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"

t_const consts[MAX_CONST];
int     num_consts = 0;

t_token token;
int     secondary_token;
char    next_char = ' ';

t_nht   table_ids, table_keywords;


void init_tables() {
  nht_create_table(&table_ids);
  nht_create_table(&table_keywords);
  nht_add(&table_keywords, "TRUE",     TOKEN_TRUE    );
  nht_add(&table_keywords, "FALSE",    TOKEN_FALSE   );
  nht_add(&table_keywords, "char",     TOKEN_CHAR    );
  nht_add(&table_keywords, "integer",  TOKEN_INTEGER );
  nht_add(&table_keywords, "boolean",  TOKEN_BOOLEAN );
  nht_add(&table_keywords, "array",    TOKEN_ARRAY   );
  nht_add(&table_keywords, "function", TOKEN_FUNCTION);
  nht_add(&table_keywords, "string",   TOKEN_STRING  );
  nht_add(&table_keywords, "var",      TOKEN_VAR     );
  nht_add(&table_keywords, "struct",   TOKEN_STRUCT  );
  nht_add(&table_keywords, "return",   TOKEN_RETURN  );
  nht_add(&table_keywords, "break",    TOKEN_BREAK   );
  nht_add(&table_keywords, "continue", TOKEN_CONTINUE);
  nht_add(&table_keywords, "while",    TOKEN_WHILE   );
  nht_add(&table_keywords, "do",       TOKEN_DO      );
  nht_add(&table_keywords, "if",       TOKEN_IF      );
  nht_add(&table_keywords, "else",     TOKEN_ELSE    );
  nht_add(&table_keywords, "type",     TOKEN_TYPE    );
  nht_add(&table_keywords, "of",       TOKEN_OF      );
}

t_token search_keyword(char* name) {
  t_token token;
  return (token = (t_token)nht_search(&table_keywords, name)) == NHT_ERROR ? TOKEN_ID : token;
}

int search_name(char* name) {
  int val;
  if ((val = nht_search(&table_ids, name)) != NHT_ERROR)
    return val;
  return nht_add(&table_ids, name, strlen(name));
}

int add_char_const(char c) {
  t_const new_const;
  new_const.type = TOKEN_CHARACTER;
  new_const.c = c;
  consts[num_consts] = new_const;
  return num_consts++;
}

int add_numeral_const(int n) {
  t_const new_const;
  new_const.type = TOKEN_NUMERAL;
  new_const.n = n;
  consts[num_consts] = new_const;
  return num_consts++;
}

int add_string_const(char* s, size_t len) {
  t_const new_const;
  new_const.type = TOKEN_STRINGVAL;

  char* new_string = (char*)malloc((len + 1) * sizeof(char));
  strcpy(new_string, s);

  new_const.s = new_string;
  consts[num_consts] = new_const;
  return num_consts++;
}

char  get_char_const   (int n) { return consts[n].c; }
int   get_numeral_const(int n) { return consts[n].n; }
char* get_string_const (int n) { return consts[n].s; }


static char readChar() { return getchar(); } // getchar -> fgetc
static char readValidChar() {
  char c;
  while (isspace(c = readChar())) ;
  return c;
}

static void setDoubleToken(char next, t_token single_token, t_token double_token) {
  next_char = readChar();
  if (next_char == next) {
    token = double_token;
    next_char = readChar();
  } else {
    token = single_token;
  }
}

t_token get_next_token() {
  if (isspace(next_char))
    next_char = readValidChar();

  if (next_char == EOF) {
    token = TOKEN_EOF;
  } else if (isalpha(next_char)) {
    char buffer[MAX_BUFFER_LEN+1];
    buffer[0] = next_char;
    size_t size = 1;

    next_char = readChar();
    while ((isalnum(next_char) || next_char == '_') && size < MAX_BUFFER_LEN) {
      buffer[size++] = next_char;
      next_char = readChar();
    }
    buffer[size] = '\0';

    token = search_keyword(buffer);
    if (token == TOKEN_ID) {
      secondary_token = search_name(buffer);
    }
  } else if (isdigit(next_char)) {
    int num = next_char-'0';

    next_char = readChar();
    while (isdigit(next_char)) {
      num = 10*num + (next_char - '0');
      next_char = readChar();
    }

    token = TOKEN_NUMERAL;
    secondary_token = add_numeral_const(num);
  } else if (next_char == '"') {
    char buffer[MAX_BUFFER_LEN+1];
    buffer[0] = '"';
    size_t size = 1;

    next_char = readChar();
    while (next_char != '"' && next_char != EOF && size < MAX_BUFFER_LEN) {
      buffer[size++] = next_char;
      next_char = readChar();
    }

    if (next_char == EOF) {
      token = TOKEN_UNKNOWN;
    } else {
      buffer[size++] = '"';
      buffer[size]   = '\0';

      token = TOKEN_STRINGVAL;
      secondary_token = add_string_const(buffer, size);
      next_char = readChar();
    }
  } else if (next_char == '\'') {
    next_char = readChar();
    if (next_char == '\'' || next_char == EOF) {
      token = TOKEN_UNKNOWN;
    } else {
      char c = next_char;
      next_char = readChar();
      if (next_char == '\'') {
        token = TOKEN_CHARACTER;
        secondary_token = add_char_const(c);
        next_char = readChar();
      } else {
        token = TOKEN_UNKNOWN;
      }
    }
  } else {
    switch (next_char) {
      case ':': next_char = readChar(); token = TOKEN_COLON;             break;
      case ';': next_char = readChar(); token = TOKEN_SEMICOLON;         break;
      case ',': next_char = readChar(); token = TOKEN_COMMA;             break;
      case '{': next_char = readChar(); token = TOKEN_LEFT_BRACES;       break;
      case '}': next_char = readChar(); token = TOKEN_RIGHT_BRACES;      break;
      case '[': next_char = readChar(); token = TOKEN_LEFT_SQUARE;       break;
      case ']': next_char = readChar(); token = TOKEN_RIGHT_SQUARE;      break;
      case '(': next_char = readChar(); token = TOKEN_LEFT_PARENTHESIS;  break;
      case ')': next_char = readChar(); token = TOKEN_RIGHT_PARENTHESIS; break;
      case '*': next_char = readChar(); token = TOKEN_TIMES;             break;
      case '/': next_char = readChar(); token = TOKEN_DIVIDE;            break;
      case '.': next_char = readChar(); token = TOKEN_DOT;               break;

      case '&': setDoubleToken('&', TOKEN_UNKNOWN, TOKEN_AND);              break;
      case '|': setDoubleToken('|', TOKEN_UNKNOWN, TOKEN_OR);               break;
      case '=': setDoubleToken('=', TOKEN_EQUAL,   TOKEN_EQUAL_EQUAL);      break;
      case '!': setDoubleToken('=', TOKEN_NOT,     TOKEN_NOT_EQUAL);        break;
      case '<': setDoubleToken('=', TOKEN_LESS,    TOKEN_LESS_OR_EQUAL);    break;
      case '>': setDoubleToken('=', TOKEN_GREATER, TOKEN_GREATER_OR_EQUAL); break;
      case '+': setDoubleToken('+', TOKEN_PLUS,    TOKEN_PLUS_PLUS);        break;
      case '-': setDoubleToken('-', TOKEN_MINUS,   TOKEN_MINUS_MINUS);      break;

      default: token = TOKEN_UNKNOWN;
    }
  }

  return token;
}
