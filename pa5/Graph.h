//-----------------------------------------------------------------------------
// Graph.h
// Header file for the List ADT
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include"List.h"

/*** NIL and INFINITY representation ***/
#define NIL 0
#define UNDEF -1

// Graph
// Exported reference type
typedef struct GraphObj* Graph;

// newGraph()
// constructor for the Graph type
Graph newGraph(int);

// freeGraph()
// destructor for the Graph type
void freeGraph(Graph* pG);

// getOrder()
// returns the order of the graph
int getOrder(Graph G);

// getSize()
// returns the size of the graph
int getSize(Graph G);

// getParent()
// returns the parent of the graph
int getParent(Graph G, int u);

// getDiscover()
// returns the discover time
int getDiscover(Graph G, int u);

// getFinish()
// returns the finish time
int getFinish(Graph G, int u);

// addEdge()
// adds an edge to the graph
void addEdge(Graph G, int u, int v);

// addArc()
// adds an arc to the graph
void addArc(Graph G, int u, int v);

// DFS()
// performs a depth first search on the graph
void DFS(Graph G, List S);

// tranpose()
// transposes the graph
Graph transpose(Graph G);

// copyGraph()
// makes a copy of the graph
Graph copyGraph(Graph G);

// printGraph()
// prints out the graph
void printGraph(FILE* out, Graph G);

#endif
