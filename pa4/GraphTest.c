// ----------------------------------------------
// Duy Nguyen
// duminguy (W1475318)
// CS 101 pa4
// 2/23/17
// GraphTest.c
// Test file for Graph ADT
// ----------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
    int i, n=35;
    List list = newList();
    Graph G = NULL;
    
    // Build graph G
    G = newGraph(n);
    for(i=1; i<n; i++){
        if( i%7!=0 ) addEdge(G, i, i+1);
        if( i<=28  ) addEdge(G, i, i+7);
    }
    addEdge(G, 9, 31);
    addEdge(G, 17, 13);
    addEdge(G, 14, 33);
    
    printf("The graph represenation:\n");
    
    // Print adjacency list representation of G
    printGraph(stdout, G);

    // get size of graph G
    printf("\nThe size is %d\n", getSize(G)); 
    
    // get order of graph G
    printf("The order is %d\n", getOrder(G)); // should be 35
    
    printf("\n");
    
    // BFS from source vertex 15
    BFS(G, 15);
    
    // print source
    printf("Source : %d\n", getSource(G)); // should be 15
    
    // print parent
    printf("Parent of 8: %d\n", getParent(G, 8)); // should be 15
    printf("Parent of 2: %d\n", getParent(G, 2)); // should be 1
    
    printf("\n");
    
    // print distance
    printf("Distance from vertex 15 to vertex 8: %d\n", getDist(G,8)); // should be 1
    printf("Distance from vertex 15 to vertex 2: %d\n", getDist(G, 2)); // should be 3
    
    printf("\n");
    
    // print path
    getPath(list, G, 2);
    printf("The distance from 15 to 2 is %d\n", getDist(G, 2)); // should be 3
    printf("The path from 15 to 2 is: "); // should be 15 8 1 2
    printList(stdout, list);
    printf("\n");
    
    printf("\n");
    
    // make graph null
    makeNull(G);
    
    // print graph (should be empty -- contain no edges)
    printGraph(stdout, G);
    
    // print size (should be 0)
    printf("\nThe size is %d", getSize(G));
    
    // print order (should be 35)
    printf("\nThe order is %d\n", getOrder(G));
    
    // print source (should be NIL (-1))
    printf("The source is %d\n", getSource(G));
    
    return(EXIT_SUCCESS);
}
