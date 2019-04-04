
// ----------------------------------------------
// Duy Nguyen
// duminguy (W1475318)
// CS 101 pa3
// 2/5/17
// List.java
// List module containing various ADT operations
// ----------------------------------------------

class List{
    
    private class Node{
        // Fields
        Object data;
        Node prev;
        Node next;
        
        // Constructor
        Node(Object data){
            this.data = data;
            prev = null;
            next = null;
        }
        
        // toString(): overrides Object's toString() method
        public String toString(){
            return String.valueOf(data);
        }
        
        // equals(): overrides Object's equals() method
        public boolean equals(Object x){
            boolean eq = false;
            Node that;
            if(x instanceof Node){
                that = (Node) x;
                eq = (this.data==that.data);
            }
            return eq;
        }
    }
    
    // Fields
    private Node front;
    private Node back;
    private Node cursor;
    private int length;
    private int cursorIndex;
    
    // Constructor
    // Creates a new empty list
    List(){
        front = null;
        back = null;
        cursor = null;
        length = 0;
        cursorIndex = -1;
    }
    
    // Access Functions ------------------------------------------------------
    
    // length()
    // Returns the number of elements in this List
    int length(){
        return length;
    }
    
    // index()
    // If cursor is defined, returns the index of the cursor element,
    // otherwise returns -1;
    int index(){
        return cursorIndex;
    }
    
    // front()
    // Returns front element
    // Pre: length()>0
    Object front(){
        if(length()<=0){
            throw new RuntimeException(
                "List Error: front() called on empty List");
        }
        return front.data;
    }
    
    // back()
    // Returns back element
    // Pre: lengt()>0
    Object back(){
        if(length()<=0){
            throw new RuntimeException(
                "List Error: back() called on empty List");
        }
        return back.data;
    }
    
    // get()
    // Returns the cursor element
    // Pre: length()>0, index()>=0
    Object get(){
        if(length()<=0){
            throw new RuntimeException(
                "List Error: get() called on empty List");
        }
        if(index()<0){
            throw new RuntimeException(
                "List Error: get() called on undefined cursor");
        }
        return cursor.data;
    }
    
    // Returns true if this List and L are the same integer sequence
    // The cursor is ignored in both lists
    public boolean equals(Object x){
        boolean eq = false;
        List L;
        Node N, M;
        
        if(x instanceof List){
            L = (List)x;
            N = this.front;
            M = L.front;
            eq = (this.length==L.length);
            while(eq && N!=null){
                eq = N.equals(M);
                N = N.next;
                M = M.next;
            }
        }
        return eq;
    }
    
    // Manipulation Procedures -----------------------------------------------
    
    // clear()
    // Resets this List to its original empty state
    void clear(){
        front = null;
        back = null;
        cursor = null;
        length = 0;
        cursorIndex = -1;
    }
    
    // moveFront()
    // If List is non-empty, places the cursor under the front element,
    // otherwise does nothing
    void moveFront(){
        if(length()>0){
            cursor = front;
            cursorIndex = 0;
        }
    }
    
    // moveBack()
    // If List is non-empty, places the cursor under the back element,
    // otherwise does nothing
    void moveBack(){
        if(length()>0){
            cursor = back;
            cursorIndex = length()-1;
        }
    }
    
    // movePrev()
    // If the cursor is defined and not at front, moves cursor one step toward
    // front of this List, if cursor is defined at front, cursor becomes undefined,
    // if cursor is undefined does nothing
    void movePrev(){
        if(cursor!=null && cursor!=front){
            cursor = cursor.prev;
            cursorIndex--;
        }else if(cursor!=null && cursor==front){
            cursor = null;
            cursorIndex = -1;
        }
    }
    
    // moveNext()
    // If cursor is defined and not at back, moves cursor one step toward
    // back of this List, if cursor is defined and at back, cursor becomes
    // undefined, if cursor is undefined does nothing
    void moveNext(){
        if(cursor!=null && cursor!=back){
            cursor = cursor.next;
            cursorIndex++;
        }else if(cursor!=null && cursor==back){
            cursor = null;
            cursorIndex = -1;
        }
    }
    
    // prepend(int data)
    // Inserts new element into this List. If List is non-empty,
    // insertion takes place before front element
    void prepend(Object data){
        Node N = new Node(data);
        if(length()==0){
            front = back = N;
        }else{ // assert length()>0
            front.prev = N;
            N.next = front;
            front = N;
        }
        length++;
    }
    
    // append(int data)
    // Insert new element into this List. If List is non-empty,
    // insertions takes place after back element
    void append(Object data){
        Node N = new Node(data);
        if(length()==0){
            front = back = N;
        }else{ // assert length()>0
            back.next = N;
            N.prev = back;
            back = N;
        }
        length++;
    }
    
    // insertBefore(int data)
    // Insert new element before cursor
    // Pre: length()>0, index()>=0
    void insertBefore(Object data){
        if(length()<=0){
            throw new RuntimeException(
                "List Error: insertBefore() called on empty List");
        }
        if(index()<0){
            throw new RuntimeException(
                "List Error: insertBefore() called on undefined cursor");
        }
        Node N = new Node(data);
        if(cursor==front){
            N.next = cursor;
            cursor.prev = N;
            front = N;
        }else{
            N.next = cursor;
            N.prev = cursor.prev;
            cursor.prev.next = N;
            cursor.prev = N;
        }
        cursorIndex++;
        length++;
    }
    
    // insertAfter(int data)
    // Inserts new element after cursor
    // Pre: length()>0, index()>=0
    void insertAfter(Object data){
        if(length()<=0){
            throw new RuntimeException(
                "List Error: insertAfter() called on empty List");
        }
        if(index()<0){
            throw new RuntimeException(
                "List Error: insertAfter() called on undefined cursor");
        }
        Node N = new Node(data);
        Node M = cursor.next;
        if(cursor==back){
            cursor.next = N;
            N.prev = cursor;
            back = N;
            //append(data);
        }else{
            cursor.next = N;
            N.prev = cursor;
            N.next = M;
            M.prev = N;
        }
        length++;
    }
    
    // deleteFront()
    // Deletes the front element
    // Pre: length()>0
    void deleteFront(){
        if(length()<=0){
            throw new RuntimeException("List Error: deleteFront() called on empty list");
        }
        if(front==back){
            front = null;
        }else{
            Node N = front;
            front = N.next;
            front.prev = null;
        }
        length--;
    }
    
    // deleteBack()
    // Deletes the back element
    // Pre: length()>0
    void deleteBack(){
        if(length()<=0){
            throw new RuntimeException("List Error: deleteBack() called on empty list");
        }
        if(back==front){
            back = null;
        }else{
            Node N = back;
            back = N.prev;
            back.next = null;
        }
        length--;
    }
    
    // delete()
    // Deletes cursor element, making cursor undefined
    // Pre: length()>0, index()>=0
    void delete(){
        if(length()<=0){
            throw new RuntimeException(
                "List Error: delete() called on an empty List");
        }
        if(index()<0){
            throw new RuntimeException(
                "List Error: delete() called on an undefined cursor");
        }
        if(cursor==front){
            deleteFront();
            cursorIndex = -1;
        }else if(cursor==back){
            deleteBack();
            cursorIndex = -1;
        }else{
            Node N = cursor.prev;
            Node M = cursor.next;
            N.next = M;
            M.prev = N;
            cursor = null;
            cursorIndex = -1;
            length--;
        }
        //length--;
    }
    
    // Other Methods ---------------------------------------------------------
    
    // toString()
    // Overrides Object's toString method, Returns a String representation
    // of this List consisting of a space separated sequence of integers,
    // with front on left
    public String toString(){
        StringBuffer sb = new StringBuffer();
        Node N = front;
        while(N!=null){
            sb.append(N.toString());
            if(N != back){
                sb.append(" ");
            }
            N = N.next;
        }
        return new String(sb);
    }
}
