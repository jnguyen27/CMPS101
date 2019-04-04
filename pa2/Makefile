#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 2
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c
clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

check1:
	valgrind --leak-check=full $(EXEBIN) ListClient

check2:
	valgrind --leak-check=full $(EXEBIN) Lex in1 out1

check3:
	valgrind --leak-check=full $(EXEBIN) Lex in2 out2

check 4:
	valgrind --leak-check=full $(EXEBIN) Lex in3 out3

submit:
	submit cmps101-pt.w17 pa2 Lex.c List.c List.h README Makefile ListClient.c
