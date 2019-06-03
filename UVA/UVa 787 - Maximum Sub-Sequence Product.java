import java.io.*;
import java.util.*;
import java.math.*;

class Main {
    public static void main (String args[]) {
        int n, idx;
        int[] nums = new int[101];
        Scanner s = new Scanner(System.in);
        while (s.hasNextInt()) {
            idx = 0;
            while (s.hasNextInt()) {
                n = s.nextInt();
                if (n == -999999) break;
                nums[idx++] = n;
            }
            BigInteger max = BigInteger.valueOf(-999999);
            BigInteger val;
            for (int i = 0; i < idx; i++) {
                val = BigInteger.valueOf(1);
                for (int j = i; j < idx; j++) {
                    val = val.multiply(BigInteger.valueOf(nums[j]));
                    if (val.compareTo(max) == 1) max = val;
                }
            }
            System.out.println(max);
        }
    }
}