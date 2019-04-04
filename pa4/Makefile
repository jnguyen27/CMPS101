#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 4
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindPath GraphClient FindPath.o GraphClient.o $(BASE_OBJECTS)

checkFind : FindPath
	$(MEMCHECK) FindPath in3 junk3

checkClient : GraphClient
	$(MEMCHECK) GraphClient

check1:
	$(MEMCHECK) FindPath in1 out1

check2:
	$(MEMCHECK) FindPath in2 out2

check3:
	$(MEMCHECK) FindPath in3 out3

check4:
	$(MEMCHECK) FindPath in4 out4

check5:
	$(MEMCHECK) FindPath in5 out5

check6:
	$(MEMCHECK) FindPath in6 out6

submit:
	submit cmps101-pt.w17 pa4 List.c List.h Graph.c Graph.h GraphTest.c FindPath.c Makefile README
