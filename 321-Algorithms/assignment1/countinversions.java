import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class countinversions {
    int mergeSort(int array[], int size) {
        int[] sorted = new int[size];
        return sorter(array, sorted, 0, size-1);
    }

    int sorter(int array[], int sorted[], int l, int r) {
        int inversions = 0;
        int m = (r+l)/2;
        if (r>l) {
            inversions += sorter(array, sorted, l, m);
            inversions += sorter(array, sorted, m + 1, r);
            inversions += merge(array, sorted, l, m + 1, r);
        }
        return inversions;
    }

    int merge(int array[], int sorted[], int l, int m, int r) {
        int inversions = 0;
        int l_index=l, m_index=m, sorted_index=l_index;
      
        while ((l_index <= m-1) && (m_index <= r)) {
            if (array[l_index] <= array[m_index]) {
                sorted[sorted_index++] = array[l_index++];
            }
            else {
                sorted[sorted_index++] = array[m_index++];
                inversions += m-l_index;
            }
        }
        while (l_index <= m-1)
            sorted[sorted_index++] = array[l_index++];
      
        while (m_index <= r)
            sorted[sorted_index++] = array[m_index++];
        for (l_index = l; l_index <= r; l_index++)
            array[l_index] = sorted[l_index];
      
        return inversions;
    }
    public static void main(String[] args) throws FileNotFoundException  {
        int temp[] = new int[1000];
        File file = new File("inversionsinput.txt");
        Scanner scanner = new Scanner(file);
        int size = 0;
        while(scanner.hasNextLine()) {
            temp[size] = Integer.parseInt(scanner.nextLine()); 
            size++;
        }
        int arr[] = new int[size];
        for(int i=0; i<size; i++)
            arr[i] = temp[i];
        scanner.close();
        System.out.println("array contains " + new countinversions().mergeSort(arr, size) + " inversions");
    }
}

