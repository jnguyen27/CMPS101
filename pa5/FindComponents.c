/*
 * Duy Nguyen
 * duminguy
 * CS101 pa5
 * 3/6/17
 * FindComponents.c
 * Checks command line arguments and takes in an
 input file and produces an output file accordingly
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"
#include"List.h"

/* function main which takes command line arguments*/
int main(int argc, char* argv[]){
    /* variables */
    FILE* in; /* file handle for input */
    FILE* out; /* file handle for output */
    int vertices = 0;
    int u, v, SCC, SCCcount;
    
    /* check command line for correct number of arguments */
    if(argc!=3){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
    }
    
    /* open input file for reading */
    in = fopen(argv[1], "r");
    if(in==NULL){
        printf("Unable to reading from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    /* open output file for writing */
    out = fopen(argv[2], "w");
    if(out==NULL){
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    /* gets the number of vertices in the graph */
    fscanf(in, "%d", &vertices);
    
    /* creating new graph with the corresponding # of vertices */
    Graph graph = newGraph(vertices);
    
    /* get coordinates of the graph and create it */
    while(fscanf(in, "%d %d", &u, &v)){
        if(u == 0 && v ==0){
            break;
        }
        addArc(graph, u, v);
    }
    
    /* prints the graph */
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, graph);
    fprintf(out, "\n");
    
    /* adds components to graph */
    List list = newList();
    for(int i=1; i<=getOrder(graph); i++){
        append(list, i);
    }
    
    /* finds strongly connected components */
    DFS(graph, list); // perform DFS on the list
    Graph transposed = transpose(graph); // transposes the graph
    SCC = 0; // counter for strongly connected components
    DFS(transposed, list);
    moveFront(list);
    while(index(list)>=0){
        int x = get(list);
        if(getParent(transposed, x)==NIL){
            SCC++;
        }
        moveNext(list);
    }

    // creates a new list array containing the number of SCC
    List SCClist[SCC];
    for(int j=0; j<SCC; j++){
        SCClist[j] = newList();
    }
    
    // fills the list array with the strongly connected components
    SCCcount = SCC; // total number of SCC (used as a decrement counter)
    moveFront(list);
    while(index(list)>=0){
        int y = get(list);
        if(getParent(transposed, y)==NIL){
            SCCcount--;
            if(SCCcount<0){
                break;
            }
        }
        append(SCClist[SCCcount], y);
        moveNext(list);
    }
    
    fprintf(out, "G contains %d strongly connected components:\n", SCC);
    for(int k=0; k<SCC; k++){
        fprintf(out, "Component %d: ", k+1);
        printList(out, SCClist[k]);
        if(k!=SCC){
            fprintf(out, "\n");
        }
        freeList(&SCClist[k]);
    }
    
    // fprintf(out, "\n");
    
    /* free memory */
    freeGraph(&graph);
    freeGraph(&transposed);
    freeList(&list);
    
    /* close files */
    fclose(in);
    fclose(out);
    
    return(EXIT_SUCCESS);
}
