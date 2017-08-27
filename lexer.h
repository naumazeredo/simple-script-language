/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 * @dependencies: C11 compiler
 *
 */

#ifndef SSC_LEXER
#define SSC_LEXER

#include <stdint.h>
#include "nothashtable.h"

#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

#define MAX_CONST 256
#define MAX_BUFFER_LEN 1024

// Token list
typedef enum {
  // reserved
  TOKEN_TRUE, TOKEN_FALSE,
  TOKEN_CHAR, TOKEN_INTEGER, TOKEN_BOOLEAN, TOKEN_ARRAY,
  TOKEN_FUNCTION, TOKEN_STRING, TOKEN_VAR, TOKEN_STRUCT,
  TOKER_RETURN, TOKEN_BREAK, TOKEN_CONTINUE,
  TOKEN_WHILE, TOKEN_DO, TOKEN_IF, TOKEN_ELSE,
  TOKEN_TYPE, TOKEN_OF,

  // symbols
  TOKEN_EOF,
  TOKEN_COLON, TOKEN_SEMICOLON, TOKEN_COMMA,
  TOKEN_EQUAL,
  TOKEN_LEFT_SQUARE, TOKEN_RIGHT_SQUARE, TOKEN_LEFT_BRACES, TOKEN_RIGHT_BRACES,
  TOKEN_LEFT_PARENTHESIS, TOKEN_RIGHT_PARENTHESIS,
  TOKEN_AND, TOKEN_OR,
  TOKEN_LESS, TOKEN_GREATER, TOKEN_LESS_OR_EQUAL, TOKEN_GREATER_OR_EQUAL,
  TOKEN_NOT_EQUAL, TOKEN_EQUAL_EQUAL,
  TOKEN_PLUS, TOKEN_MINUS, TOKEN_TIMES, TOKEN_DIVIDE,
  TOKEN_PLUS_PLUS, TOKEN_MINUS_MINUS,
  TOKEN_DOT, TOKEN_NOT,

  // regular tokens
  TOKEN_CHARACTER, TOKEN_NUMERAL, TOKEN_STRINGVAL, TOKEN_ID,

  // unknown
  TOKEN_UNKNOWN,

  // size
  TOKEN_NUM
} t_token;


// Constants
typedef struct {
  uint8_t type;
  union {
    char  c;
    int   n;
    char* s;
  };
} t_const;

void    init_tables();
t_token searchKeyword(char* name);
int     searchName(char* name);

int   addCharConst   (char  c);
int   addNumeralConst(int   n);
int   addStringConst (char* s, size_t len);
char  getCharConst   (int n);
int   getNumeralConst(int n);
char* getStringConst (int n);

void getNextToken();

extern t_const aConsts[MAX_CONST];
extern int     nNumConsts;

extern t_token token;
extern int     secondary_token;
extern char    next_char;

extern t_nht   table_ids, table_keywords;

#endif //SCC_LEXER
