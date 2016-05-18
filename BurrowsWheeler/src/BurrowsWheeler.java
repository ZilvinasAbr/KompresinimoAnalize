
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;
import javax.swing.*;

class BurrowsWheeler {

    public static void main(String[] param) throws FileNotFoundException {

        String text = new Scanner(new File("C:\\Users\\Tomas\\Desktop\\test.txt")).useDelimiter("\\Z").next();
        System.out.println(text);

        final int SIZE = text.length();

        String[] rotations = new String[SIZE];
        String result = "";
        String compressed = "";

        System.out.println(SIZE + " rotations");
        System.out.println();

// First generate all rotations
        generateRotations(text, rotations);
        printStringArray(rotations, SIZE);

// Next sort those strings  
        sortStrings(rotations, SIZE);
        printStringArray(rotations, SIZE);

// Finally take the last character of each sorted string to
// get the Burrows-Wheeler transform
        result = lastChars(rotations, SIZE);
        System.out.println(result);
        System.out.println();

// Now you can compress the Burrows-Wheeler transform
// and get a much compressed string even with no runs of
// repeated letters in the original   
        compressed = runLengthEncode(result);
        PrintWriter out = new PrintWriter("C:\\Users\\Tomas\\Desktop\\filename.txt");
        out.println(compressed);
        out.close();
        System.out.println(compressed);
        System.out.println("Compressed length: " + compressed.length());
        System.out.println();
        System.exit(0);
    }

  // **********************************************
    // Do run length encoding on a string
    public static String runLengthEncode(String source) {
        String result = "";
        int count = 1;
        char current = source.charAt(0);

        for (int i = 1; i < source.length(); i++) {
            if (source.charAt(i) == current) {
                count = count + 1;
            } else {
                result = result + count + current;
                count = 1;
                current = source.charAt(i);
            }
        }
        result = result + count + current;

        return result;
    }

  // **********************************************
    // Generate all the rotations of a String, rotating one position at a time
    public static void generateRotations(String source, String[] s) {
        s[0] = source;

        for (int i = 1; i < source.length(); i++) {
            s[i] = s[i - 1].substring(1) + s[i - 1].charAt(0);
        }
    }

  // **********************************************
    // Get each of the last characters of an array of Strings
    public static String lastChars(String[] s, int SIZE) {
        String result = "";

        for (int i = 0; i < SIZE; i++) {
            result = result + s[i].charAt(SIZE - 1);
        }

        return result;
    }

  // **********************************************
    // Sort an array of strings 
    public static void printStringArray(String[] a, int SIZE) {
        for (int i = 0; i < SIZE; i++) {
            System.out.println(a[i]);
        }
        System.out.println();

    }

  // **********************************************
    // Sort an array of strings 
    public static void sortStrings(String[] a, int SIZE) {
        for (int pass = 0; pass <= SIZE - 2; pass++) {
            for (int i = 0; i <= SIZE - pass - 2; i++) {
                if (a[i].compareTo(a[i + 1]) > 0) {
                    swap(a, i, i + 1);
                }
            }
        }
    }

  // **********************************************
    // Swap 2 given positions in an array of Strings 
    public static void swap(String[] a, int i, int j) {
        String t = a[i];
        a[i] = a[i + 1];
        a[i + 1] = t;
    }

}
