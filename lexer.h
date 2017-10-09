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
#include "tokens.h"

#define MAX_CONST 256
#define MAX_BUFFER_LEN 1024

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
t_token search_keyword(char* name);
int     search_name(char* name);

int   add_char_const   (char  c);
int   add_numeral_const(int   n);
int   add_string_const (char* s, size_t len);
char  get_char_const   (int n);
int   get_numeral_const(int n);
char* get_string_const (int n);

t_token get_next_token();

extern t_const consts[MAX_CONST];
extern int     num_consts;

extern t_token token;
extern int     secondary_token;
extern char    next_char;

extern t_nht   table_ids, table_keywords;

#endif //SCC_LEXER
