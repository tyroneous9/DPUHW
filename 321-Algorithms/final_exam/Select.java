//Wesley Wu

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;
class select {

    static int quick_select(int[] A, int k) {
        return quick_select_aux(A, 0, A.length-1, k);
    }

    static int quick_select_aux(int[] A, int l, int n, int k) {
        if(n==l) return A[l];
        int randInt = new Random().nextInt(n-l+1)+1;
        int p = partition(A, l, n, randInt);
        if(k < p)
            return quick_select_aux(A, l, p-1, k);
        else if(k > p) 
            return quick_select_aux(A, p+1, n, k-p);
        else 
            return A[p];
    }

    static void swap(int[] A, int i, int j) {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    static int partition(int[] A, int l, int n, int p) {
        //swap p and nth element
        swap(A, p, n);
        int numsLess = l;
        for(int i=l; i<=n; i++)
            if(A[i]<A[n]) {
                swap(A, numsLess, i);
                numsLess++;
            }
        swap(A, numsLess+1, n);
        return numsLess+1;
    }

    public static void main(String args[]) throws FileNotFoundException {
        int[] temp = new int[1000];
        File file = new File("feselect.txt");
        Scanner scanner = new Scanner(file);
        int size=0;
        while(scanner.hasNextInt()) {
            temp[size] = scanner.nextInt();
            size++;
        }
        int[] A = new int[size];
        for(int i=0; i<size; i++)
            A[i] = temp[i];
        System.out.println(quick_select(A, 4)+" k=4");
        System.out.println(quick_select(A, A.length/2)+" k=n/2");
        System.out.println(quick_select(A, A.length-1)+" k=n-1");
    }
}