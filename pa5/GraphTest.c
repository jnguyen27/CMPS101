// ----------------------------------------------
// Duy Nguyen
// duminguy (W1475318)
// CS 101 pa5
// 3/6/17
// GraphTest.c
// Test file for Graph ADT
// ----------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
    int i, n=8;
    List S = newList();
    Graph G = newGraph(n);
    Graph T=NULL, C=NULL;
    
    for(i=1; i<=n; i++) append(S, i);
    
    addArc(G, 1,2);
    addArc(G, 1,5);
    addArc(G, 2,5);
    addArc(G, 2,6);
    addArc(G, 3,2);
    addArc(G, 3,4);
    addArc(G, 3,6);
    addArc(G, 3,7);
    addArc(G, 3,8);
    addArc(G, 6,5);
    addArc(G, 6,7);
    addArc(G, 8,4);
    addArc(G, 8,7);
    printGraph(stdout, G);
    
    fprintf(stdout, "\n");
    fprintf(stdout, "This is the order of G:\n");
    printf("The order is %d\n", getOrder(G)); // should print 8
    fprintf(stdout, "\n");
    
    fprintf(stdout, "This is the size of G:\n");
    printf("The order is %d\n", getSize(G)); // should print 13
    fprintf(stdout, "\n");
    
    DFS(G, S);
    getDiscover(G, 1); // should be 1
    getParent(G, 1); // should be NIL (0)
    getFinish(G, 1); // should be 10
    
    getDiscover(G, 8); // should be 14
    getParent(G, 8); // should be 3
    getFinish(G, 8); // should be 15
    
    printList(stdout, S); // should print out 3 8 4 1 2 6 7 5
    fprintf(stdout, "\n");
    
    T = transpose(G);
    C = copyGraph(G);
    fprintf(stdout, "\n");
    fprintf(stdout, "This is a copy of the graph:\n");
    printGraph(stdout, C);
    fprintf(stdout, "\n");
    fprintf(stdout, "This is the transpose of the graph:\n");
    printGraph(stdout, T);
    
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);
    
    return(EXIT_SUCCESS);
}
