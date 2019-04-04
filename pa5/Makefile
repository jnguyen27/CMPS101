#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 4
#
#  make                     makes FindComponents
#  make GraphTest           makes GraphTest
#  make clean               removes binaries
#  make checkFind           tests FindComponents for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c99 -Wall
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindComponents : FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindComponents.o : FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

FindComponents : FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean :
	$(REMOVE) FindComponents GraphClient GraphTest FindComponents.o GraphClient.o GraphTest.o $(BASE_OBJECTS)

checkFind : FindComponents
	$(MEMCHECK) FindComponents in3 junk3

checkClient : GraphClient
	$(MEMCHECK) GraphClient

checkTest : GraphTest
	$(MEMCHECK) GraphTest

check1: FindComponents
	$(MEMCHECK) FindComponents in1 out1

check2: FindComponents
	$(MEMCHECK) FindComponents in2 out2

check3: FindComponents
	$(MEMCHECK) FindComponents in3 out3

check4: FindComponents
	$(MEMCHECK) FindComponents in4 out4

check5: FindComponents
	$(MEMCHECK) FindComponents in5 out5

check6: FindComponents
	$(MEMCHECK) FindComponents in6 out6

check7: FindComponents
	$(MEMCHECK) FindComponents in7 out7
 
submit:
	submit cmps101-pt.w17 pa5 README Makefile List.c List.h Graph.h Graph.c GraphTest.c FindComponents.c
