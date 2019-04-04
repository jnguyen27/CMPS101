/*
 * Duy Nguyen
 * duminguy
 * CS101 pa5
 * 3/6/17
 * List.c
 * Graph module with ADT operations
 */

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

/*** color representations ***/
#define WHITE 1
#define GRAY 2
#define BLACK 3

// structs -----------------------------------------------------

/*** private GraphObj type ***/
typedef struct GraphObj{
    List *adjacencyList;
    int *parent; // initially NIL
    int *color; // initially WHITE
    int *discover; // initially UNDEF
    int *finish; // intially UNDEF
    int order;
    int size; // initially 0
} GraphObj;

/*** Constructors-Destructors ***/

// returns a new graph pointing to a newly
// created GraphObj representing a graph
// having n vertices and no edges
Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->adjacencyList = calloc(n+1, sizeof(List));
    G->parent = calloc(n+1, sizeof(int));
    G->color = calloc(n+1, sizeof(int));
    G->discover = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    for(int i=1; i<=n; i++){
        G->adjacencyList[i] = newList();
        G->parent[i] = NIL;
        G->color[i] = WHITE;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    return G;
}

// frees all dynamic memory associated with
// Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG){
    for(int i=1; i<=getOrder(*pG); i++){
        freeList(&(*pG)->adjacencyList[i]);
    }
    if(pG!=NULL && *pG!=NULL){
        free((*pG)->adjacencyList);
        free((*pG)->parent);
        free((*pG)->color);
        free((*pG)->discover);
        free((*pG)->finish);
        free(*pG);
        *pG = NULL;
    }
}

/*** Access functions ***/

// returns the field value order
int getOrder(Graph G){
    if(G==NULL){
        printf("Graph Error: getOrder() called on a NULL Graph referenece\n");
        exit(1);
    }
    return G->order;
}

// returns the field value size
int getSize(Graph G){
    if(G==NULL){
        printf("Graph Error: getSize() called on a NULL Graph reference\n");
        exit(1);
    }
    return G->size;
}

// returns the parent of the vertex u in
// Breadth-First tree created by BFS(),
// or NIL if BFS() has not yet been called
// Pre: 1<=u<=getOrder(G)
int getParent(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        printf("Graph Error: getParent() called on invalid Graph reference\n");
        exit(1);
    }
    return G->parent[u];
}

// returns the the most recently discover vertex (time)
// used in function DFS()
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        printf("Graph Error: getParent() called on invalid Graph reference\n");
        exit(1);
    }
    return G->discover[u];
}

// returns the finish time
// Pre: 1<=u<=n]getOrder(G)
int getFinish(Graph G, int u){
    if(u < 1 || u > getOrder(G)){
        printf("Graph Error: getParent() called on invalid Graph reference\n");
        exit(1);
    }
    return G->finish[u];
}

/*** Manipulation procedures ***/

// inserts a new edge joining u to v, i.e. u
// is added to the adjacency List of v, and v
// to the adjaceny List of u
// Pre: two int arguments in range 1 to getOrder(G)
void addEdge(Graph G, int u, int v){
    if((u < 1 || u > getOrder(G)) || (v < 1 || v > getOrder(G))){
        printf("Graph Error: addEdge() called on invalid Graph reference\n");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

// inserts a new directed edge from u to v, i.e.
// v is added to the adjacency List of u (but
// not u to the adjacency List of v)
// Pre: two int arguments in range 1 to getOrder(G)
void addArc(Graph G, int u, int v){
    if((u < 1 || u > getOrder(G)) || (v < 1 || v > getOrder(G))){
        printf("Graph Error: addEdge() called on invalid Graph reference\n");
        exit(1);
    }
    List list = G->adjacencyList[u];
    moveFront(list);
    while(index(list)>=0 && get(list) < v){
        moveNext(list);
    }
    if(index(list)==-1){
        append(list, v);
    }else{
        insertBefore(list, v);
    }
    G->size++;
}

// private helper function called on from DFS
void Visit(Graph G, List S, int x, int *time){
    if(G==NULL){
        printf("Graph Error: calling Visit() on a NULL Graph reference\n");
        exit(1);
    }
    if(S==NULL){
        printf("Graph Error: calling Visit() on a NULL List reference\n");
        exit(1);
    }
    G->color[x] = GRAY;
    G->discover[x] = ++*time;
    List list = G->adjacencyList[x];
    moveFront(list);
    while(index(list)>=0){
        int y = get(list);
        if(G->color[y] == WHITE){
            G->parent[y] = x;
            Visit(G, S, y, time);
        }
        moveNext(list);
    }
    prepend(S, x);
    G->color[x] = BLACK;
    G->finish[x] = ++*time;
}

// runs the DFS algorithm on the Graph G with
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S){
    if(G==NULL){
        printf("Graph Error: calling DFS() on NULL Graph reference\n");
        exit(1);
    }
    if(S==NULL){
        printf("Graph Error: calling Visit() on a List Graph reference\n");
        exit(1);
    }
    if(length(S)!=getOrder(G)){
        printf("Graph Error: calling DFS() on invalid Graph reference \n");
        exit(1);
    }
    for(int i=1; i<=getOrder(G); i++){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    int time = 0;
    moveFront(S);
    while(index(S)>=0){
        int x = get(S);
        if(G->color[x] == WHITE){
            Visit(G, S, x, &time);
        }
        moveNext(S);
    }
    for(int j=1; j<=getOrder(G); j++){
        deleteBack(S);
    }
}

/*** Other operations ***/

// transposes the graph G
Graph transpose(Graph G){
    if(G==NULL){
        printf("Graph Error: copyGraph() called on NULL Graph reference\n");
        exit(1);
    }
    Graph transpose = newGraph(getOrder(G));
    for(int i=1; i<=getOrder(G); i++){
        List list = G->adjacencyList[i];
        moveFront(list);
        while(index(list)>=0){
            addArc(transpose, get(list), i);
            moveNext(list);
        }
    }
    return transpose;
}

// makes a copy of the Graph G
Graph copyGraph(Graph G){
    if(G==NULL){
        printf("Graph Error: copyGraph() called on NULL Graph reference\n");
        exit(1);
    }
    Graph copy = newGraph(getOrder(G));
    for(int i=1; i<=getOrder(G); i++){
        List list = G->adjacencyList[i];
        moveFront(list);
        while(index(list)>=0){
            addArc(copy, i, get(list));
            moveNext(list);
        }
    }
    return copy;
}

// prints the adjacency list representation of G
// to the file pointed to by out
void printGraph(FILE* out, Graph G){
    if(out == NULL || G == NULL){
        printf("Graph Error: printGraph() called on NULL graph reference\n");
        exit(1);
    }
    for(int i=1; i<=getOrder(G); i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adjacencyList[i]);
        fprintf(out, "\n");
    }
}
