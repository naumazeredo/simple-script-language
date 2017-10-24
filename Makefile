
all:
	gcc -Wall -std=c11 main.c lexer.c nothashtable.c queue.c parser_gen.c parser.c scope.c semantics.c -o sslc.out

run:
	./sslc.out < program.ssp > program.ftw
