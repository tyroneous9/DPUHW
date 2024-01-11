//Wesley Wu

class LIS {

    static int fastLIS(int[] A) {
        A[0] = Integer.MIN_VALUE;
        int i, j;
        int n = A.length;
        int[][] LISbigger = new int[n][n+1];
        for(i=0; i<n; i++)
            LISbigger[i][n] = 0;
        for(j=n-1; j>0; j--)
            for(i=0; i<j; i++) {
                int keep = 1+LISbigger[j][j+1];
                int skip = LISbigger[i][j+1];
                if(A[i]>=A[j]) LISbigger[i][j] = skip;
                else LISbigger[i][j] = Math.max(keep, skip);
            }
        return LISbigger[0][1];
    }

    public static void main(String args[]) {
        int[] A = {237, 252, 53, 80, 248, 248, 115, 218, 104, 24, 33, 121, 176, 70, 210, 80, 171, 237, 251, 191, 47, 222, 139, 151, 213, 74, 80, 7, 219, 170, 107, 218};
        System.out.println("LIS = "+fastLIS(A));
    }
}
