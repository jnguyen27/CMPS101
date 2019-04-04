//-----------------------------------------------------------------------------
// Graph.h
// Header file for the List ADT
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include"List.h"

/*** NIL and INFINITY representation ***/
#define NIL -1
#define INF -2

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

// getSourse()
// returns the source of the graph
int getSource(Graph G);

// getParent()
// returns the parent of the graph
int getParent(Graph G, int u);

// getDist()
// returns the distance of the graph
int getDist(Graph G, int u);

// getPath()
// returns the path of the graph
void getPath(List L, Graph G, int u);

// makeNull()
// makes the graph null
void makeNull(Graph G);

// addEdge()
// adds an edge to the graph
void addEdge(Graph G, int u, int v);

// addArc()
// adds an arc to the graph
void addArc(Graph G, int u, int v);

// BFS()
// performs a breadth first search on the graph
void BFS(Graph G, int s);

// printGraph()
// prints out the graph
void printGraph(FILE* out, Graph G);

#endif
