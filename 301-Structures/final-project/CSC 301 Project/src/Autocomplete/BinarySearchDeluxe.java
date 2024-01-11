package Autocomplete;

import java.util.Comparator;
import java.util.TreeSet;

public class BinarySearchDeluxe {

    // Returns the index of the first key in the sorted array a[]
    // that is equal to the search key, or -1 if no such key.
    public static <Key> int firstIndexOf(Key[] a, Key key, Comparator<Key> comparator) {
    	int leftIndex = 0, rightIndex = a.length-1, midIndex;
    	int compareVal;
    	while(leftIndex <= rightIndex) {
    		midIndex = (leftIndex+rightIndex)/2;
    		compareVal = comparator.compare(key, a[midIndex]);
    		if(compareVal == 0) {
    			//looks for left-most key
    			if(midIndex==0) {
    				return midIndex;
    			}
    			while(comparator.compare(key, a[midIndex-1]) == 0) {
    				midIndex -= 1;
    				if(midIndex==0) {
    					break;
    				}
    			}
        		return midIndex;
        	}
    		else if(compareVal < 0) {
        		rightIndex = midIndex-1;
        	}
        	else if(compareVal > 0) {
        		leftIndex = midIndex+1;
        	}
        }
    	return -1;
    }

    // Returns the index of the last key in the sorted array a[]
    // that is equal to the search key, or -1 if no such key.
    public static <Key> int lastIndexOf(Key[] a, Key key, Comparator<Key> comparator) {
    	
    	int leftIndex = 0, rightIndex = a.length-1, midIndex;
    	int compareVal;
    	while(leftIndex <= rightIndex) {
    		midIndex = (leftIndex+rightIndex)/2;
    		compareVal = comparator.compare(key, a[midIndex]);
    		if(compareVal == 0) {
    			//looks for right-most key
    			if(midIndex==a.length-1) {
    				return midIndex;
    			}
    			while(comparator.compare(key, a[midIndex+1]) == 0) {
    				midIndex += 1;
    				if(midIndex==a.length-1) {
    					break;
    				}
    			}
        		return midIndex;
        	}
    		else if(compareVal < 0) {
        		rightIndex = midIndex-1;
        	}
        	else if(compareVal > 0) {
        		leftIndex = midIndex+1;
        	}
        }
    	return -1;
    }
}