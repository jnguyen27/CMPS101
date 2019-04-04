// ------------------------------------------------
// Duy Nguyen
// duminguy (W1475318)
// CS 101 pa3
// 2/5/17
// Matrix.java
// Matrix module containing various ADT operations
// ------------------------------------------------

class Matrix{
    
    private class Entry{
        // Fields
        int column;
        double value;
        
        // Constructor
        Entry(int column, double value){
            this.column = column;
            this.value = value;
        }
        
        // toString(): overrides Object's toString() method
        public String toString(){
            return("("+column+", "+value+")");
        }
        
        // equals(): overrides Object's equals() method
        public boolean equals(Object x){
            boolean eq = false;
            Entry that;
            if(x instanceof Entry){
                that = (Entry) x;
                eq = (this.column == that.column && this.value==that.value);
            }
            return eq;
        }
        
    }
    
    // Fields
    private int size; // number of rows/columns
    private int NNZ; // number of non-zero entries
    private List[] row;
    
    // Constructor
    // Makes a new n x n zero Matrix. pre: n>=1
    Matrix(int n){
        if(n<1){
            throw new RuntimeException(
                                       "Matrix Error: cannot initial a matrix of less than size 1");
        }
        size = n;
        row = new List[n+1];
        for(int i=1; i<=n; i++){
            row[i] = new List();
        }
    }
    
    // Access functions ----------------------------------------------------
    
    // Returns n, the number of rows and columns of this Matrix
    int getSize(){
        return size;
    }
    
    // Returns the number of non-zero entries in this Matrix
    int getNNZ(){
        return NNZ;
    }
    
    // overrides Object's equals() method
    public boolean equals(Object x){
        boolean eq = false;
        Matrix M;
        Entry K, L;
        if(x instanceof Matrix){
            M = (Matrix)x;
            eq = (this.getSize() == M.getSize());
            if(eq == true){
                for(int i=1; i<=getSize(); i++){
                    row[i].moveFront();
                    M.row[i].moveFront();
                    while(row[i].index()>=0 && M.row[i].index()>=0){
                        K = (Entry)this.row[i].get();
                        L = (Entry)M.row[i].get();
                        eq = K.equals(L);
                        row[i].moveNext();
                        M.row[i].moveNext();
                    }
                }
            }
        }
        return eq;
    }
    
    // Manipulation procedures ----------------------------------------------
    
    // sets this Matrix to the zero state
    void makeZero(){
        for(int i=1; i<=getSize(); i++){
            row[i] = new List();
        }
        NNZ = 0;
    }
    
    // returns a new Matrix having the same entries as this Matrix
    Matrix copy(){
        Matrix newMatrix = new Matrix(getSize());
        for(int i=1; i<=getSize(); i++){
            for(row[i].moveFront(); row[i].index()>=0; row[i].moveNext()){
                Entry entry = (Entry)row[i].get();
                newMatrix.row[i].append(new Entry(entry.column, entry.value));
                newMatrix.NNZ++;
            }
        }
        return newMatrix;
    }
    
    // changes ith row, jth column of this Matrix to x
    // pre: 1<=i<=getSize(), 1<=j<=getSize()
    void changeEntry(int i, int j, double x){
        if((i<1) || (i>getSize()) || (j<1) || (j>getSize())){
            throw new RuntimeException(
                                       "Matrix Error: changeEntry() called on invalid matrices");
        }
        boolean column = false;
        Entry newEntry = new Entry(j, x);
        row[i].moveFront();
        while(row[i].index() >= 0) {
            Entry entry = (Entry) row[i].get();
            column = (entry.column == j ? true : false);
            if(column){ // if(column == j){
                if(x == 0.0) {
                    row[i].delete();
                    NNZ--;
                    return;
                } else {
                    entry.value = x;
                    return;
                }
            }
            row[i].moveNext();
        }
        if(!column && x != 0.0) {
            row[i].moveFront();
            if(row[i].index() == -1){ // if the row is empty
                row[i].append(new Entry(j, x));
                NNZ++;
                return;
            } else {
                while(row[i].index() >= 0 && ((Entry)(row[i].get())).column < j){
                    row[i].moveNext();
                }
                if(row[i].index() >= 0){
                    row[i].insertBefore(newEntry);
                    NNZ++;
                    return;
                }else{ // if(row[i].index()==-1){
                    row[i].append(newEntry);
                    NNZ++;
                    return;
                }
            }
        }
    }
    
    // returns a new Matrix that is the scalar product of this Matrix with x
    Matrix scalarMult(double x){
        Matrix newMatrix = new Matrix(getSize());
        for(int i=1; i<=getSize(); i++){
            for(row[i].moveFront(); row[i].index()>=0; row[i].moveNext()){
                Entry entry = (Entry)(row[i].get());
                double scalar = entry.value*x;
                newMatrix.row[i].append(new Entry(entry.column, scalar));
                newMatrix.NNZ++;
            }
        }
        return newMatrix;
    }
    
    // returns a new Matrix that is the sum of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix add(Matrix M){
        if(getSize()!=M.getSize()){
            throw new RuntimeException(
                                       "Matrix Error: add() called on different sized matrices");
        }
        Matrix newMatrix = new Matrix(getSize());
        if(this == M){
            newMatrix = this.scalarMult(2.0);
        }else{
            for(int i=1; i<=getSize(); i++){
                if(row[i].length() > 0 && M.row[i].length() == 0){
                    row[i].moveFront();
                    while(row[i].index() >= 0){
                        Entry entry = (Entry)(row[i].get());
                        newMatrix.row[i].append(new Entry(entry.column, entry.value));
                        newMatrix.NNZ++;
                        row[i].moveNext();
                    }
                }else if(row[i].length() == 0 && M.row[i].length() > 0){
                    M.row[i].moveFront();
                    while(M.row[i].index() >= 0){
                        Entry entry = (Entry)(M.row[i].get());
                        newMatrix.row[i].append(new Entry(entry.column, entry.value));
                        newMatrix.NNZ++;
                        M.row[i].moveNext();
                    }
                }else{ // if(row[i].length > 0 && M.row[i].length() > 0){
                    row[i].moveFront();
                    M.row[i].moveFront();
                    while(row[i].index() >= 0 && M.row[i].index() >= 0){
                        Entry entry1 = (Entry)(row[i].get());
                        Entry entry2 = (Entry)(M.row[i].get());
                        if(entry1.column < entry2.column){
                            newMatrix.row[i].append(new Entry(entry1.column, entry1.value));
                            newMatrix.NNZ++;
                            row[i].moveNext();
                            if(row[i].index() == -1){
                                while(M.row[i].index() != -1){
                                    entry2 = (Entry)(M.row[i].get());
                                    newMatrix.row[i].append(new Entry(entry2.column, entry2.value));
                                    newMatrix.NNZ++;
                                    M.row[i].moveNext();
                                }
                            }
                        }else if(entry1.column > entry2.column){
                            newMatrix.row[i].append(new Entry(entry2.column, entry2.value));
                            NNZ++;
                            M.row[i].moveNext();
                            if(M.row[i].index() == -1){
                                while(row[i].index() != -1){
                                    entry1 = (Entry)(row[i].get());
                                    newMatrix.row[i].append(new Entry(entry1.column, entry1.value));
                                    newMatrix.NNZ++;
                                    row[i].moveNext();
                                }
                            }
                        }else{ // if(entry1.column == entry2.column){
                            double sum = entry1.value + entry2.value;
                            if(sum != 0){
                                newMatrix.row[i].append(new Entry(entry1.column, sum));
                                newMatrix.NNZ++;
                            }
                            row[i].moveNext();
                            M.row[i].moveNext();
                            if(row[i].index() == -1 && M.row[i].index() != -1){
                                while(M.row[i].index() != -1){
                                    entry2 = (Entry)(M.row[i].get());
                                    newMatrix.row[i].append(new Entry(entry2.column, entry2.value));
                                    newMatrix.NNZ++;
                                    M.row[i].moveNext();
                                }
                            }else if(row[i].index() != -1 && M.row[i].index() == -1){
                                while(row[i].index() != -1){
                                    entry1 = (Entry)(row[i].get());
                                    newMatrix.row[i].append(new Entry(entry1.column, entry1.value));
                                    newMatrix.NNZ++;
                                    row[i].moveNext();
                                }
                            }
                        }
                    }
                }
            }
        }
        return newMatrix;
    }
    
    // returns a new Matrix that is the difference of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix sub(Matrix M){
        if(getSize()!=M.getSize()){
            throw new RuntimeException(
                                       "Matrix Error: sub() called on different sized matrices");
        }
        Matrix newMatrix = new Matrix(getSize());
        if(this == M){
            return newMatrix;
        }else{
            for(int i=1; i<=getSize(); i++){
                if(row[i].length() > 0 && M.row[i].length() == 0){
                    row[i].moveFront();
                    while(row[i].index()>=0){
                        Entry entry = (Entry)(row[i].get());
                        newMatrix.row[i].append(new Entry(entry.column, entry.value));
                        newMatrix.NNZ++;
                        row[i].moveNext();
                    }
                }else if(row[i].length() == 0 && M.row[i].length() > 0){
                    M.row[i].moveFront();
                    while(M.row[i].index()>=0){
                        Entry entry = (Entry)(M.row[i].get());
                        newMatrix.row[i].append(new Entry(entry.column, entry.value*(-1.0)));
                        newMatrix.NNZ++;
                        M.row[i].moveNext();
                    }
                }else{ // if(row[i].length() > 0 && M.row[i].length() > 0){
                    row[i].moveFront();
                    M.row[i].moveFront();
                    while(row[i].index() >= 0 && M.row[i].index() >= 0){
                        Entry entry1 = (Entry)(row[i].get());
                        Entry entry2 = (Entry)(M.row[i].get());
                        if(entry1.column < entry2.column){
                            newMatrix.row[i].append(new Entry(entry1.column, entry1.value));
                            newMatrix.NNZ++;
                            row[i].moveNext();
                            if(row[i].index() == -1){
                                while(M.row[i].index() != -1){
                                    entry2 = (Entry)(M.row[i].get());
                                    newMatrix.row[i].append(new Entry(entry2.column, entry2.value*(-1.0)));
                                    newMatrix.NNZ++;
                                    M.row[i].moveNext();
                                }
                            }
                        }else if(entry1.column > entry2.column){
                            newMatrix.row[i].append(new Entry(entry2.column, entry2.value*(-1.0)));
                            NNZ++;
                            M.row[i].moveNext();
                            if(M.row[i].index() == -1){
                                while(row[i].index() != -1){
                                    entry1 = (Entry)(row[i].get());
                                    newMatrix.row[i].append(new Entry(entry1.column, entry1.value));
                                    newMatrix.NNZ++;
                                    row[i].moveNext();
                                }
                            }
                        }else{ // if(entry1.column == entry2.column){
                            double diff = entry1.value - entry2.value;
                            if(diff != 0){
                                newMatrix.row[i].append(new Entry(entry1.column, diff));
                                newMatrix.NNZ++;
                            }
                            row[i].moveNext();
                            M.row[i].moveNext();
                            if(row[i].index() == -1 && M.row[i].index() != -1){
                                while(M.row[i].index() != -1){
                                    entry2 = (Entry)(M.row[i].get());
                                    newMatrix.row[i].append(new Entry(entry2.column, entry2.value*(-1.0)));
                                    newMatrix.NNZ++;
                                    M.row[i].moveNext();
                                }
                            }else if(row[i].index() != -1 && M.row[i].index() == -1){
                                while(row[i].index() != -1){
                                    entry1 = (Entry)(row[i].get());
                                    newMatrix.row[i].append(new Entry(entry1.column, entry1.value));
                                    newMatrix.NNZ++;
                                    row[i].moveNext();
                                }
                            }
                        }
                    }
                    
                }
            }
        }
        return newMatrix;
    }
    
    // returns a new Matrix that is the transpose of this Matrix
    Matrix transpose(){
        Matrix newMatrix = new Matrix(getSize());
        for(int i=1; i<=getSize(); i++){
            for(row[i].moveFront(); row[i].index()>=0; row[i].moveNext()){
                Entry entry = (Entry)(this.row[i].get());
                newMatrix.row[entry.column].append(new Entry(i, entry.value));
                newMatrix.NNZ++;
            }
        }
        return newMatrix;
    }
    
    // returns a new Matrix that is the product of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix mult(Matrix M){
        if(getSize()!=M.getSize()){
            throw new RuntimeException(
                                       "Matrix Error: mult() called on different sized matrices");
        }
        Matrix newMatrix = new Matrix(getSize());
        Matrix transMatrix = M.transpose();
        for(int i=1; i<=getSize(); i++){
            if(row[i].length() > 0){
                for(int j=1; j<=getSize(); j++){
                    if(transMatrix.row[j].length() > 0){
                        double product = dot(row[i], transMatrix.row[j]);
                        if(product != 0){
                            newMatrix.row[i].append(new Entry(j, product));
                            newMatrix.NNZ++;
                        }
                    }
                }
            }
        }
        return newMatrix;
    }
    
    // Other functions -----------------------------------------------------
    
    // overrides Object's toString() method
    public String toString(){
        String s = "";
        for(int i=1; i<=getSize(); i++){
            if(row[i].length()>0){
                s += i + ": " + row[i].toString()+"\n";
            }
        }
        return s;
    }
    
    // helpful private function with signature
    private static double dot(List P, List Q){
        double dotProduct = 0.0;
        P.moveFront();
        Q.moveFront();
        while(P.index()>=0 && Q.index()>=0){
            Entry listP = (Entry)(P.get());
            Entry listQ = (Entry)(Q.get());
            if(listP.column < listQ.column){
                P.moveNext();
            }else if(listP.column > listQ.column){
                Q.moveNext();
            }else{ // if(listP.column == listQ.column){
                if(listP.value!=0 || listQ.value!=0){
                    dotProduct += (listP.value*listQ.value);
                }
                P.moveNext();
                Q.moveNext();
            }
        }
        return dotProduct;
    }
}
