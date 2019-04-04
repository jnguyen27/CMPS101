/*
 * Duy Nguyen
 * duminguy
 * CS101 pa2
 * 1/23/17
 * List.c
 * Implementing the List ADT in C
 */

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

// structs ------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
    int data;
    struct NodeObj* prev;
    struct NodeObj* next;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursorIndex;
} ListObj;

// List
typedef ListObj* List;

// Constructor-Destructors

// newNode()
// returns reference to new Node object. Initializes next data fields
// Private.
Node newNode(int data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return N;
}

// newList
// constructor for private List type
List newList(void){
    List L = malloc(sizeof(ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
    return L;
}
// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL
// Private.
void freeNode(Node* pN){
    if(pN!=NULL && *pN!=NULL){
        free(*pN);
        *pN = NULL;
    }
}

// freeList()
// Frees heap memory pointed to by *pL, sets *pL to NULL
// Private.
void freeList(List *pL){
    if(pL!=NULL && *pL!=NULL){
	while(length(*pL)>0){
	    deleteBack(*pL);
	}
	free(*pL);
	*pL = NULL;
    }
}

// Access functions ------------------------------------------

// length()
// Returns the number of elements in this List
int length(List L){
    if(L==NULL){
	printf("List Error: length() called on NULL List reference\n");
	exit(1);
    }
    return L->length;
}

// index()
// If cursor is defined returns the index of the cursor element,
// otherwise returns -1
int index(List L){
    return L->cursorIndex;
}

// front()
// Returns front element
// Pre: length()>0
int front(List L){
    if(length(L)<=0){
        printf("List Error: front() called on empty list\n");
        exit(1);
    }
    if(L==NULL){
	printf("List Error: front() called on NULL List refeence\n");
	exit(1);
    }
    return L->front->data;
}

// back()
// Returns back element
// Pre: length()>0
int back(List L){
    if(length(L)<=0){
        printf("List Error: back() called on empty list\n");
        exit(1);
    }
    return L->back->data;
}

// get()
// Returns the cursor element
// Pre: length()>0, index()>=0
int get(List L){
    if(L==NULL){
	printf("List Error: get() called on NULL List reference\n");
	exit(1);
    }
    if(length(L)<=0){
        printf("List Error: get() called on empty list\n");
        exit(1);
    }
    if(index(L)<0){
        printf("List Error: get() called on undefined cursor\n");
        exit(1);
    }
    return L->cursor->data;
}

// Returns true if this A and B are the same integer sequence
// The cursor is ignored in both lists
int equals(List A, List B){
    Node N, M;
    if(length(A)==length(B)){
        N = A->front;
        M = B->front;
	if(N->data == M->data){
	    while(N->next != NULL && M->next != NULL){
                N = N->next;
		M = M->next;
		if(A->back->data == B->back->data){
		    return 1;
                }
	    }
	}
    } 
    return 0;
}

// Manipulation procedures ------------------------------------

// clear()
// Resets this List to its original empty state
void clear(List L){
    if(L==NULL){
	printf("List Error: clear() called on NULL List reference\n");
	exit(1);
    }
    if(L != NULL){
	    while(length(L)>0){
	        deleteBack(L);
	    }
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->cursorIndex = -1;
}

// moveFront()
// If List is non-empty, places the cursor the front element,
// otherwise does nothing
void moveFront(List L){
    if(L==NULL){
	printf("List Error: moveFront() called on NULL List reference\n");
	exit(1);
    }
    if(length(L)>0){
        L->cursor = L->front;
        L->cursorIndex = 0;
    }
}

// moveBack()
// If List is non-empty, places the cursor under the back element,
// otherwise does nothing
void moveBack(List L){
    if(L==NULL){
	printf("List Error: moveBack() called on NULL List reference\n");
	exit(1);
    }
    if(length(L)>0){
        L->cursor = L->back;
        L->cursorIndex = length(L)-1;
    }
}

// movePrev()
// If the cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined at front, cursor becomes undefined,
// if cursor is undefined does nothing
void movePrev(List L){
    if(L->cursor!=NULL && L->cursor!=L->front){
        L->cursor = L->cursor->prev;
        L->cursorIndex--;
    }else if(L->cursor!=NULL && L->cursor==L->front){
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
}

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing
void moveNext(List L){
    if(L->cursor!=NULL && L->cursor!=L->back){
        L->cursor = L->cursor->next;
        L->cursorIndex++;
    }else if(L->cursor!=NULL && L->cursor==L->back){
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
}

// prepend()
// Inserts new element into this List. If List is non-empty,
// insertion takes place before front element
void prepend(List L, int data){
    Node N = newNode(data);
    if(length(L)==0){
        L->front = L->back = N;
    }else{ // assert length()>0
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
    }
    if(L->cursorIndex != -1){
	L->cursorIndex++;
    }
    L->length++;
}

// append()
// Inserts new element into this List. If List is non-empty,
// insertion takes place after back element
void append(List L, int data){
    Node N = newNode(data);
    if(length(L)==0){
        L->front = L->back = N;
    }else{ // assert length()>0
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    }
    L->length++;
}

// insertBefore()
// Insert new element before cursor
// Pre: length()>0, index()>=0
void insertBefore(List L, int data){
    if(L==NULL){
	printf("List Error: insertBefore() called on NULL List reference\n");
	exit(1);
    }
    if(length(L)<=0){
        printf("List Error: insertBefore() called on empty List\n");
        exit(1);
    }
    if(index(L)<0){
        printf("List Error: insertBefore() called on undefined cursor\n");
        exit(1);
    }
    Node N = newNode(data);
    if(L->cursor == L->front){
        N->next = L->cursor;
        L->cursor->prev = N;
        L->front = N;
    }else{
        N->next = L->cursor;
        N->prev = L->cursor->prev;
        L->cursor->prev->next = N;
        L->cursor->prev = N;
    }
    L->cursorIndex++;
    L->length++;
}

// insertAfter()
// Inserts new element after cursor
// Pre: length()>0, index()>=0
void insertAfter(List L, int data){
    if(L==NULL){
	printf("List Error: insertAfter() called on NULL List reference\n");
	exit(1);
    }
    if(length(L)<=0){
        printf("insertAfter() called on empty List\n");
        exit(1);
    }
    if(index(L)<0){
        printf("insertAfter() called on undefined cursor\n");
        exit(1);
    }
    Node N = newNode(data);
    Node M = L->cursor->next;
    if(L->cursor == L->back){
        L->cursor->next = N;
        N->prev = L->cursor;
        L->back = N;
    }else{
        L->cursor->next = N;
        N->prev = L->cursor;
        N->next = M;
        M->prev = N;
    }
    L->length++;
}

// deleteFront()
// Deletes the front element
// Pre: length()>0
void deleteFront(List L){
    if(L==NULL){
        printf("List Error: deleteFront() called on NULL List reference\n");
        exit(1);
    }
    if(length(L)<=0){
        printf("List Error: deleteFront() called on empty List\n");
        exit(1);
    }
    if(L->front == L->back){
        Node N = L->front;
	L->front = NULL;
        freeNode(&N);
    }else{
        Node N = L->front;
        L->front = N->next;
        L->front->prev = NULL;
        freeNode(&N);
    }
    L->length--;
}

// deleteBack()
// Deletes the back element
// Pre: length()>0
void deleteBack(List L){
    if(L==NULL){
        printf("List Error: deleteBack() called on NULL List reference\n");
        exit(1);
    }
    if(length(L)<=0){
        printf("List Error: deleteBack() called on empty List\n");
        exit(1);
    }
    if(L->back == L->front){
	Node N = L->back;
        L->back = NULL;
        freeNode(&N);
    }else{
        Node N = L->back;
        L->back = N->prev;
        L->back->next = NULL;
        freeNode(&N);
    }
    L->length--;
}

// delete()
// Deletes cursor element, making cursor undefined
// Pre: length()>0, index()>=0
void delete(List L){
    if(L==NULL){
        printf("List Error: delete() called on NULL List reference\n");
        exit(1);
    }
    if(length(L)<=0){
        printf("List Error: delete() called on an empty List\n");
        exit(1);
    }
    if(index(L)<0){
        printf("List Error: delete() called on an undefined cursor\n");
        exit(1);
    }
    if(L->cursor == L->front){
        deleteFront(L);
        L->cursorIndex = -1;
    }else if(L->cursor == L->back){
        deleteBack(L);
        L->cursorIndex = -1;
    }else{
        Node N = L->cursor->prev;
        Node M = L->cursor->next;
        N->next = M;
        M->prev = N;
        freeNode(&(L->cursor));
        L->cursorIndex = -1;
        L->length--;
    }
}

// Other operations ------------------------------------------

// printList()
// pre: none
// prints a text representation of L to the file point to by out
void printList(FILE* out, List L){
    Node N = L->front;
    while(N!=NULL){
        fprintf(out, "%d ", N->data);;
        N = N->next;
    }
}

// copyList()
// Returns a new List representing the same integer sequence as this List
// The cursor in the new List is undefined, regardless of the state of the
// cursor in this List. This List is unchanged
List copyList(List L){
    List list = newList();
    Node N = L->front;
    while(N != NULL){
        append(list, N->data);
        N = N->next;
    }
    return list;
}
