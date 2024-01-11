import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class DCMaximum {
    public static int arrayMax(int[] arr, int left, int right) {
        int mid = (left+right)/2;
        if (left>=right) 
            return arr[left];
        int l = arrayMax(arr, 0, mid);
        int r = arrayMax(arr, mid+1, right);
        if (l > r)
            return l;
        return r;
    }
    public static void main(String[] args) throws FileNotFoundException {
        int temp[] = new int[1000];
        File file = new File("numbers.txt");
        Scanner scanner = new Scanner(file);
        int size = 0;
        while(scanner.hasNextLine()) {
            temp[size] = Integer.parseInt(scanner.nextLine()); 
            size++;
        }
        int arr[] = new int[size];
        for(int i=0; i<size; i++)
            arr[i] = temp[i];

        int max = arrayMax(arr, 0, size-1);
        System.out.println("MAX = "+max);
        scanner.close();
    }
}
