all:
	gcc -std=c11 main.c lexer.c nothashtable.c -o lexer.out

run:
	./lexer.out < program.ssp > program.lex
