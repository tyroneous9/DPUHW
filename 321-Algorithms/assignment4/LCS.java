class LCS {
    static int findLCS(String x, String y) {
        //initialization
        int m = x.length();
        int n = y.length();
        int[][] table = new int[m][n];
        int i, j;
        //fill table
        for(i=0; i<m; i++)
            table[i][0] = 0;
        for(j=0; j<n; j++)
            table[0][j] = 0;
        for(i=1; i<m; i++) {
            for(j=1; j<n; j++) {
                if(x.charAt(i) == y.charAt(j))
                    table[i][j] = table[i-1][j-1] + 1;
                else
                    table[i][j] = (table[i-1][j] > table[i][j-1]) ? table[i-1][j] : table[i][j-1];
            }
        }
        return table[m-1][n-1];
    }
    public static void main(String[] args) {
        String str1 = "GTTAATGTAGCTTAATAACAAAGCAAAGCACTGAAAATGCTTAGATGGATAATTGTATCCCATAA";
        String str2 = "GTTAATGTAGCTTAATTACAAAGCAAGGCACTGAAAATGCCTAGATGAGTACGCGCTACTCCATA";
        System.out.println(findLCS(str1, str2));
    }
}