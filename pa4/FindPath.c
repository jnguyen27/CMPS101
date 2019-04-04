/*
 * Duy Nguyen
 * duminguy
 * CS101 pa4
 * 1/23/17
 * FindPath.c
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
    int u, v;
    int source, destination;
    
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
        addEdge(graph, u, v);
    }
    
    /* prints the graph */
    printGraph(out, graph);
    
    /* gets and prints out the path to out */
    List list = newList();
    while(fscanf(in, "%d %d", &source, &destination)){
        if(source == 0 && destination ==0){
            break;
        }
        BFS(graph, source);
        int distance = getDist(graph, destination);
        getPath(list, graph, destination);
        if(distance == -2){ // if distance is INF
            fprintf(out, "\nThe distance from %d to %d is infinity\n", source, destination);
            fprintf(out, "No %d-%d path exists\n", source, destination);
        }else{ // if distance is not infinity
            fprintf(out, "\nThe distance from %d to %d is %d\n", source, destination, distance);
            fprintf(out, "A shortest %d-%d path is: ", source, destination);
            printList(out, list);
            fprintf(out, "\n");
        }
        clear(list);
    }
    
    /* free memory */
    freeGraph(&graph);
    freeList(&list);
    
    /* close files */
    fclose(in);
    fclose(out);
    
    return(EXIT_SUCCESS);
}
