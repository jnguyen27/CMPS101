/*
 * Duy Nguyen
 * duminguy
 * CS101 pa2
 * 1/23/17
 * Lex.c
 * Checks command line arguments and creates a new string array
 * and prints the sorted array to out
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

/* function main which takes command line arguments*/
int main(int argc, char* argv[]){
    /* variables */
    FILE* in; /* file handle for input */
    FILE* out; /* file handle for output */
    char line[100];
    int lineNumbers = 0, k = 0;
    int j, x, i;
    
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
    
    /* determining the number of lines */
    while(fgets(line, 100, in) != NULL){
        lineNumbers++;
    }
    
    /* close in file */
    fclose(in);
    
    /* creating new array of strings that is length lineNumbers */
    char *words[lineNumbers];
    
    /* reopens the file */
    in = fopen(argv[1], "r");
    
    // char *nl;
    /* places content of each line into the array of strings */
    while(fgets(line, 100, in) != NULL){
        words[k] = malloc(strlen(line)+1);
        strcpy(words[k], line);
        if(words[k][strlen(line)-1] == '\n'){
            words[k][strlen(line)-1] = '\0';
        }
        k++;
    }
    
    /* creating a new empty list */
    List list = newList();
    
    /* adding the first element of the array into the empty list */
    append(list, 0);
    
    /* sorting the array in terms of value to indices */
    for(j=1; j<lineNumbers; j++){
        moveFront(list);
        x = get(list);
        while(index(list)>=0){
            while(strcmp(words[j], words[x])>0 && index(list)<length(list)-1){
                moveNext(list);
                x = get(list);
            }
            if(strcmp(words[j], words[x])<=0){
                insertBefore(list, j);
                break;
            }else{ /* if(strcmp(words[j], words[x])>0) */
                insertAfter(list, j);
                break;
            }
        }
    }
    
    /* printing out the content of the indices to out */
    moveFront(list);
    for(i=0; i<lineNumbers; i++){
        fprintf(out, "%s\n", words[get(list)]);
        moveNext(list);
    }
    
    // frees array and list
    for(k=0; k<lineNumbers; k++){
        free(words[k]);
    }
    freeList(&list);
    
    /* close files */
    fclose(in);
    fclose(out);
    
    return(EXIT_SUCCESS);
}