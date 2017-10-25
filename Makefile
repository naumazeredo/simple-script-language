
all:
	gcc -std=c11 main.c lexer.c nothashtable.c stack.c parser_gen.c parser.c scope.c semantics.c -o sslc.out

run: all
	./sslc.out < program.ssp
