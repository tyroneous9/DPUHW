package Autocomplete;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class Autocomplete {

	Term[] terms;
    // Initializes the data structure from the given array of terms.
    public Autocomplete(Term[] terms) {
    	this.terms = terms;
    	Arrays.sort(this.terms);
    }

    // Returns all terms that start with the given prefix, in descending order of weight.
    public Term[] allMatches(String prefix) {
    	int firstIndex = BinarySearchDeluxe.firstIndexOf(terms, new Term(prefix,0), Term.byPrefixOrder(prefix.length()));
    	int secondIndex = BinarySearchDeluxe.lastIndexOf(terms, new Term(prefix,0), Term.byPrefixOrder(prefix.length()));
		Term[] matches = new Term[numberOfMatches(prefix)];
		matches = Arrays.copyOfRange(terms, firstIndex, secondIndex+1);
    	Arrays.sort(matches,Term.byReverseWeightOrder());
    	return matches;
    }

    // Returns the number of terms that start with the given prefix.
    public int numberOfMatches(String prefix) {
    	return 1 + BinarySearchDeluxe.lastIndexOf(terms, new Term (prefix,0), Term.byPrefixOrder(prefix.length())) - 
    			BinarySearchDeluxe.firstIndexOf(terms, new Term (prefix,0), Term.byPrefixOrder(prefix.length())); 
    }

    // unit testing (required)
    public static void main(String[] args) throws FileNotFoundException {
    	// read in the terms from a file
    	File file = new File("movies.txt");
        Scanner reader = new Scanner(file);
        int n = Integer.parseInt(reader.nextLine());
        Term[] terms = new Term[n];
        for(int i=0; i<n; i++) {
        	String[] elements = reader.nextLine().split("	");
        	String query = elements[0];
        	long weight = Long.parseLong(elements[1]);
        	terms[i] = new Term(query, weight);
        }
        reader.close();
        Autocomplete autocomplete = new Autocomplete(terms);
        //indices 140-180
        System.out.println(autocomplete.numberOfMatches("The"));
        System.out.println(Arrays.toString(autocomplete.allMatches("The")));
        System.out.println("num matches="+autocomplete.allMatches("The").length);
    }
}