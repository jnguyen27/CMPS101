// ---------------------------------------------------------------
// Duy Nguyen
// duminguy (W1475318)
// CS 101 pa1
// 1/10/17
// Lex.java
// Checks command line arguments and creates a new stiring array
// ---------------------------------------------------------------
import java.util.Scanner;
import java.io.*;

class Lex{
    
    public static void main(String[] args) throws IOException {
        // check that the number of command line arguments is exactly 2
        if(args.length!=2){
            System.err.println("Usage: Lex inFile outFile");
            System.exit(1);
        }
        
        // variables
        Scanner in = new Scanner(new File(args[0]));
        PrintWriter out = new PrintWriter(new FileWriter(args[1]));
        int n = 0;
        
        // determining the number of lines
        while(in.hasNextLine()){
            in.nextLine();
            n++;
        }
        
        // close in file
        in.close();
        
        // creating new array of strings that is length n
        String[] words = new String[n];
        
        // reopens the file
        in = new Scanner(new File(args[0]));
        
        // places content of each line into the array of strings
        for(int i=0; i<n; i++){
            words[i] = in.nextLine();
        }
        
        // creating a new empty list
        List list = new List();
        
        // adding the first element of the array into the empty list
        list.append(0);
        
        // sorting of the array in terms of value to indices
        for(int j=1; j<n; j++){
            list.moveFront();
            int x = list.get();
            while(list.index()>=0){
                while(words[j].compareTo(words[x])>0 && list.index() < list.length()-1){
                    list.moveNext();
                    x = list.get();
                }
                if(words[j].compareTo(words[x])<=0){
                    list.insertBefore(j);
                    break;
                }else{ // if(words[j].compareTo(words[x])>0)
                    list.insertAfter(j); // list.append(j) also works
                    break;
                }
            }
        }
    
        // printing out the content of the indices to out
        list.moveFront();
        for(int i=0; i<n; i++){
            out.println(words[list.get()]);
            list.moveNext();
        }
        
        // close files
        in.close();
        out.close();
    }
}
