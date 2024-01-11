package AutocompleteTests;

import static org.junit.Assert.assertEquals;

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;

import org.junit.jupiter.api.Test;

import Autocomplete.Autocomplete;
import Autocomplete.BinarySearchDeluxe;
import Autocomplete.Term;

public class AutocompleteTests {
	
	Term[] sortedTerms = new Term[] {new Term("AA", 1), new Term("AB", 1), new Term("AC", 1), 
									new Term("BA", 1), new Term("BB", 1), new Term("BC", 1),
									new Term("CA", 1), new Term("CB", 1), new Term("CC", 1)};
	
	@Test
	public void testTerm() {
		ArrayList<Term> uut = new ArrayList<Term>(4);
		uut.add(new Term("AA", 1));
		uut.add(new Term("BD", 2));
		uut.add(new Term("AB", 3));
		uut.add(new Term("BC", 4));
		
		uut.sort(Term.byPrefixOrder(2));
		String[] expectedPrefixOrder = new String[] {"AA", "AB", "BC", "BD"};
		for(int i=0; i<expectedPrefixOrder.length; i++) {
			assertEquals(expectedPrefixOrder[i], uut.get(i).query);
		}
		
		uut.sort(Term.byReverseWeightOrder());
		long[] expectedWeightOrder = new long[] {4, 3, 2, 1};
		for(int i=0; i<expectedWeightOrder.length; i++) {
			assertEquals(expectedWeightOrder[i], uut.get(i).weight);
		}
	}
	
	@Test
	public void testBinarySearchDeluxe() {
		Arrays.sort(sortedTerms);
		assertEquals(0, BinarySearchDeluxe.firstIndexOf(sortedTerms, new Term("A", 1), Term.byPrefixOrder(1)));
		assertEquals(2, BinarySearchDeluxe.lastIndexOf(sortedTerms, new Term("A", 1), Term.byPrefixOrder(1)));
		assertEquals(3, BinarySearchDeluxe.firstIndexOf(sortedTerms, new Term("B", 1), Term.byPrefixOrder(1)));
		assertEquals(5, BinarySearchDeluxe.lastIndexOf(sortedTerms, new Term("B", 1), Term.byPrefixOrder(1)));
		assertEquals(6, BinarySearchDeluxe.firstIndexOf(sortedTerms, new Term("C", 1), Term.byPrefixOrder(1)));
		assertEquals(8, BinarySearchDeluxe.lastIndexOf(sortedTerms, new Term("C", 1), Term.byPrefixOrder(1)));
	}
	public void testAutocomplete() throws FileNotFoundException {
        Autocomplete autocomplete = new Autocomplete(sortedTerms);
        Term[] expectedA = Arrays.copyOfRange(sortedTerms, 0, 2);
        Term[] expectedB = Arrays.copyOfRange(sortedTerms, 3, 5);
        Term[] expectedC = Arrays.copyOfRange(sortedTerms, 6, 8);
        for(int i=0; i<3; i++) {
        	assertEquals(expectedA.length, autocomplete.numberOfMatches("a"));
        	assertEquals(expectedA[i], autocomplete.allMatches("a")[i]);
        	assertEquals(expectedB.length, autocomplete.numberOfMatches("b"));
        	assertEquals(expectedB[i], autocomplete.allMatches("b")[i]);
        	assertEquals(expectedC.length, autocomplete.numberOfMatches("c"));
        	assertEquals(expectedC[i], autocomplete.allMatches("c")[i]);
        }
	}
}