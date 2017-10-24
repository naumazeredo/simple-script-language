/**
 *  Simple Scripting Language
 *
 * @author: Naum Azeredo Fernandes Barreira, Pedro Lucas Porto Almeida
 *
 */

#ifndef SSL_SEMANTICS
#define SSL_SEMANTICS

#include "scope.h"

typedef struct {
  t_nonterminal type;
  int nSize;
  union {
    struct {
      pobject obj;
      int name;
    } ID;
    struct {
    	pobject type;
    } T,E,L,R,Y,F,LV;
    struct {
        pobject type;
        pobject param;
        int err;
    } MC;
    struct {
        int label;
    } MT,ME,MW,MA;
    struct{
        pobject type;
        pobject param;
        int err;
        int n;
    } LE;
    struct {
        pobject list;
    } LI,DC,LP;
    struct {
        pobject type;
        int val;
    } TRU,FALS;
    struct {
        pobject type;
        int pos;
        char val;
    } CHR;
    struct {
        pobject type;
        char* val;
        int pos;
    } STR;
    struct {
        pobject type;
        int val;
        int pos;
    } NUM;
  };
} t_attrib;

void open_file();
void semantics(int rule);

#endif //SSL_SEMANTICS
