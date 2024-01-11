package Autocomplete;
import java.util.Comparator;

public class Term implements Comparable<Term> {
	public String query;
	public long weight;
    // Initializes a term with the given query string and weight.
    public Term(String query, long weight) {
    	this.query = query;
    	this.weight = weight;
    }
    
    // Compares the two terms in descending order by weight.
    public static Comparator<Term> byReverseWeightOrder() {
        return new Comparator<Term>() {
			public int compare(Term term1, Term term2) {
        		return -1 * Long.compare(term1.weight, term2.weight);
			}
        };
    }

    // Compares the two terms in lexicographic order,
    // but using only the first r characters of each query.
    public static Comparator<Term> byPrefixOrder(int r) {
    	return new Comparator<Term>() {
			public int compare(Term term1, Term term2) {
        		return term1.query.substring(0, r).compareTo(term2.query.substring(0, r));
			}
        };
    }

    // Compares the two terms in lexicographic order by query.
    public int compareTo(Term that) {
    	return query.compareTo(that.query);
    }

    // Returns a string representation of this term in the following format:
    // the weight, followed by a tab, followed by the query.
    public String toString() {
    	return weight + "	" + query;
    }
}