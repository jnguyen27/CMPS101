// ----------------------------------------------
// Duy Nguyen
// duminguy (W1475318)
// CS 101 pa3
// 2/5/17
// MatrixTest.java
// Test file for Matrix ADT
// ----------------------------------------------
public class MatrixTest{
    public static void main(String[] args){
        int i, j, n=100000;
        Matrix A = new Matrix(n);
        Matrix B = new Matrix(n);
        
        A.changeEntry(1,1,1); B.changeEntry(1,1,1);
        A.changeEntry(1,2,2); B.changeEntry(1,2,0);
        A.changeEntry(1,3,3); B.changeEntry(1,3,1);
        A.changeEntry(2,1,4); B.changeEntry(2,1,0);
        A.changeEntry(2,2,5); B.changeEntry(2,2,1);
        A.changeEntry(2,3,6); B.changeEntry(2,3,0);
        A.changeEntry(3,1,7); B.changeEntry(3,1,1);
        A.changeEntry(3,2,8); B.changeEntry(3,2,1);
        A.changeEntry(3,3,9); B.changeEntry(3,3,1);
        
        System.out.println("THIS IS MATRIX A WITH # OF NNZ:");
        System.out.println(A.getNNZ());
        System.out.println(A);
        
        System.out.println("THIS IS MATRIX B WITH # OF NNZ:");
        System.out.println(B.getNNZ());
        System.out.println(B);
        
        System.out.println("THIS IS MATRIX A SCALAR OF 1.5:");
        Matrix C = A.scalarMult(1.5);
        System.out.println(C.getNNZ());
        System.out.println(C);
        
        /* System.out.println("------------------------------------");
        System.out.println("The Matrix A is:");
        System.out.println(A);
        System.out.println("------------------------------------"); */
        
        System.out.println("THIS IS MATRIX D WITH # OF NNZ:");
        Matrix D = A.add(A);
        System.out.println(D.getNNZ());
        System.out.println(D);
        
        System.out.println("THIS IS MATRIX E WITH # OF NNZ:");
        Matrix E = A.sub(B);
        System.out.println(E.getNNZ());
        System.out.println(E);
        
        System.out.println("THIS IS MATRIX F WITH # OF NNZ:");
        Matrix F = B.transpose();
        System.out.println(F.getNNZ());
        System.out.println(F);
        
        System.out.println("THIS IS B.TRANSPOSE():");
        System.out.println(B.transpose());
        
        Matrix G = B.mult(B);
        System.out.println(G.getNNZ());
        System.out.println(G);
        // System.out.println("Ignore MULT() which has 7 non-zeros");
        System.out.println("The above is the mult output");
        
        
        /* System.out.println("------------------------------------");
        System.out.println("Matrix A is:");
        System.out.println(A);
        System.out.println("------------------------------------"); */
        
        Matrix H = A.copy();
        System.out.println(H.getNNZ());
        System.out.println("THIS IS MATRIX H:");
        System.out.println(H);
        
        System.out.println("THIS IS MATRIX A:");
        System.out.println(A);
        
        System.out.println("THIS IS THE RESULT OF A.EQUALS(H):");
        System.out.println(A.equals(H));
        
        System.out.println();
        
        System.out.println("THIS IS THE RESULT OF H.EQUALS(A):");
        System.out.println(H.equals(A));
        
        System.out.println();
        
        System.out.println("THIS IS THE RESULT OF H.EQUALS(H):");
        System.out.println(H.equals(H));
        
        System.out.println();
        
        System.out.println("THIS IS THE RESULT OF B.EQUALS(B):");
        System.out.println(B.equals(B));
        
        System.out.println();
        
        System.out.println("THIS IS THE RESULT OF A.EQUALS(B):");
        System.out.println(A.equals(B));
        
        System.out.println();
        
        System.out.println("THIS IS THE RESULT OF A.EQUALS(A):");
        
        System.out.println(A.equals(A));
        // System.out.println("Ignore the EQUALS() which has true, false, true");
        
        A.makeZero();
        System.out.println(A.getNNZ());
        System.out.println(A);
    }
}
