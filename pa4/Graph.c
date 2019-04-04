/*
 * Duy Nguyen
 * duminguy
 * CS101 pa4
 * 1/23/17
 * List.c
 * Graph module with ADT operations
 */

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

/*** color representations ***/
#define WHITE 0
#define GRAY 1
#define BLACK 2

// structs -----------------------------------------------------

/*** private GraphObj type ***/
typedef struct GraphObj{
    List *adjacencyList;
    int *parent; // initially NIL
    int *color; // initially white
    int *distance; // initially infinity
    int order;
    int size; // initially 0
    int source; // intially NIL
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
    G->distance = calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    for(int i=1; i<=n; i++){
        G->adjacencyList[i] = newList();
        G->parent[i] = NIL;
        G->color[i] = WHITE;
        G->distance[i] = INF;
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
        free((*pG)->distance);
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

// returns the source vertex most recently
// used in function BFS(), or NIL if BFS()
// has not yet been called
int getSource(Graph G){
    if(G==NULL){
        printf("Graph Error: getSource called on a NULL Graph reference\n");
        exit(1);
    }
    return G->source;
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

// returns the distance from the most recent
// BFS source to vertex u, or INF if BFS()
// has not yet been called
// Pre: 1<=u<=getOrder(G)
int getDist(Graph G, int u){
    if(getSource(G)==NIL){
        return INF;
    }
    if(u < 1 || u > getOrder(G)){
        printf("Graph Error: getDist() called on invalid Graph reference\n");
        exit(1);
    }
    return G->distance[u];
}


// appends to the list L the vertices of a
// shortest path in G from source u, or
// appends to L the value NIL if no such
// path exists
// Pre: getSource(G)!=NIL and 1<=u<=getOrder(G)
void getPath(List L, Graph G, int u){
    if(getSource(G)==NIL){
        printf("Graph Error: getPath() called on Graph with NIL source");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)){
        printf("Graph Error: getPath() called on invalid Graph reference\n");
        printf("WHY IS THIS BEING REACHED???\n");
        printf("This is u = %d\n", u);
        printf("This is getOrder() = %d\n", getOrder(G));
        exit(1);
    }
    if(u == G->source){
        append(L, u);
    }else if(G->parent[u] == NIL){
        append(L, NIL);
    }else if(G->source!=NIL){
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
    
}

/*** Manipulation procedures ***/

// deletes all the edges of G, restoring it
// to its original (no edge) state
void makeNull(Graph G){
    if(G==NULL){
        printf("Graph Error: makeNull called on NULL Graph reference\n");
        exit(1);
    }
    for(int i=1; i<=getOrder(G); i++){
        clear(G->adjacencyList[i]);
        G->parent[i] = NIL;
        G->color[i] = WHITE;
        G->distance[i] = INF;
        
    }
    G->size = 0;
    G->source = NIL;
}

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
    if(index(list) == -1){
        append(list, v);
    }else{
        insertBefore(list, v);
    }
    G->size++;
}

// runs the BFS algorithm on the Graph G with
// source s, setting the color, distance, parent.
// and source fields of G accordingly
void BFS(Graph G, int s){
    if(G==NULL){
        printf("Graph Error: calling BFS() on NULL Graph reference\n");
        exit(1);
    }
    for(int i=1; i<=getOrder(G); i++){
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->source = s;
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList();
    prepend(Q, s);
    for(moveFront(Q); index(Q)>=0; moveNext(Q)){
        int x = get(Q);
        List list = G->adjacencyList[x];
        for(moveFront(list); index(list)>=0; moveNext(list)){
            int y = get(list);
            if(G->color[y] == WHITE){
                G->color[y] = GRAY;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Q, y);
            }
        }
        G->color[x] = BLACK;
    }
    freeList(&Q);
}

/*** Other operations ***/

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
