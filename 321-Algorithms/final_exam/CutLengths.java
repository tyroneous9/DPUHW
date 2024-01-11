//Wesley Wu

class CutLengths {
    static int[] cutLengths(int n) {
        int[] lengths = {20, 10, 5, 2, 1};
        int[] numCuts = new int[lengths.length];
        int i=0;
        while(n!=0) {
            if(lengths[i]<=n) {
                n -= lengths[i];
                numCuts[i] += 1;
            }
            else
                i++;
        }
        return numCuts;
    }

    static void printCuts(int n) {
        int[] cuts = cutLengths(n);
        int[] lengths = {20, 10, 5, 2, 1};
        System.out.println("Board length: "+n);
        for(int i=0; i<cuts.length; i++)
            System.out.println("piece size: "+lengths[i]+"    count:"+cuts[i]);
    }

    public static void main(String args[]) {
        printCuts(22);
        printCuts(19);
        
    }
}
