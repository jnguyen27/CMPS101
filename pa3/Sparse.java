// ---------------------------------------------------
// Duy Nguyen
// duminguy (W1475318)
// CS 101 pa3
// 2/5/17
// Sparse.java
// Takes in input file and creates output file (matrix)
// ----------------------------------------------------
import java.io.*;
import java.util.Scanner;

public class Sparse{
    public static void main(String[] args) throws IOException{
        // check that the number of command line arguments is exactly 2
        if(args.length!=2){
            System.err.println("Usage: Sparse inFile outFile");
            System.exit(1);
        }
        
        // variables
        Scanner in = new Scanner(new File(args[0]));
        PrintWriter out = new PrintWriter(new FileWriter(args[1]));
        Matrix A, B;
        
        int n = in.nextInt(); // # of rows in the matrix
        int a = in.nextInt(); // # of NNZ entries in first matrix
        int b = in.nextInt(); // # of NNZ entries in second matrix
        
        A = new Matrix(n);
        B = new Matrix(n);
        
        for(int i=1; i<=a; i++){
            int row = in.nextInt();
            int column = in.nextInt();
            double value = in.nextDouble();
            A.changeEntry(row, column, value);
        }
        
        for(int j=1; j<=b; j++){
            int row = in.nextInt();
            int column = in.nextInt();
            double value = in.nextDouble();
            B.changeEntry(row, column, value);
        }
        
        // printing A
        out.println("A has " + A.getNNZ() + " non-zero entries:");
        out.println(A);
        
        // printing B
        out.println("B has " + B.getNNZ() + " non-zero entries:");
        out.println(B);
        
        // printing (1.5)A
        out.println("(1.5)*A =");
        Matrix C = A.scalarMult(1.5);
        out.println(C);
        
        // printing A + B
        out.println("A+B =");
        Matrix D = A.add(B);
        out.println(D);
        
        // printing A + A
        out.println("A+A =");
        Matrix E = A.add(A);
        out.println(E);
        
        // printing B - A
        out.println("B-A =");
        Matrix F = B.sub(A);
        out.println(F);
        
        // printing A - A
        out.println("A-A =");
        Matrix G = A.sub(A);
        out.println(G);
        
        // printing A^T
        out.println("Transpose(A) =");
        Matrix H = A.transpose();
        out.println(H);
        
        // printing AB
        out.println("A*B =");
        Matrix I = A.mult(B);
        out.println(I);
        
        // printing B^2
        out.println("B*B =");
        Matrix J = B.mult(B);
        out.println(J);
        
        // close scanner and printwriter
        in.close();
        out.close();
    }
}
