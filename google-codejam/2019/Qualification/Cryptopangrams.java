import java.math.BigInteger;
import java.util.*;
import java.io.*;

class Solution {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
        int t = in.nextInt(); // Scanner has functions to read ints, longs, strings, chars, etc.
        for (int i = 1; i <= t; ++i) {
            BigInteger n = in.nextBigInteger();
            int l = in.nextInt();
            ArrayList<BigInteger> values = new ArrayList<>();
            for (int j = 0; j < l; j++) {
                BigInteger x = in.nextBigInteger();
                values.add(x);
            }
            TreeSet<BigInteger> primes = new TreeSet<>();

            TreeSet<BigInteger> candidates = new TreeSet<>();
            for (int j = 0; j < l - 1; j++) {
                if (values.get(j).equals(values.get(j + 1))) continue;
                BigInteger gcd = values.get(j).gcd(values.get(j+1));
                candidates.add(gcd);
                candidates.add(values.get(j).divide(gcd));
                candidates.add(values.get(j+1).divide(gcd));
            }

            BigInteger first = null;
            for (BigInteger prev : candidates) {
                BigInteger orig = prev;
                if (!prev.isProbablePrime(200)) continue;
                boolean bad = false;
                for (int j = 0; j < l; j++) {
                    BigInteger cur = values.get(j);

                    if (cur.gcd(prev).equals(BigInteger.ONE)) {
                        bad = true;
                        break;
                    }

                    primes.add(cur.divide(prev));
                    prev = cur.divide(prev);
                }
                if (bad) continue;
                first = orig;
                primes.add(first);
                break;
            }

            if (first == null) {
                throw new Exception("first is null");
            }

            HashMap<BigInteger, Character> mapping = new HashMap<>();
            int ct = 0;
            for (BigInteger x : primes) {
                mapping.put(x, (char) ('A' + ct++));
            }

            System.out.print("Case #" + i + ": " + mapping.get(first));
            BigInteger cur = first;
            for (BigInteger x : values) {
                System.out.print(mapping.get(x.divide(cur)));
                cur = x.divide(cur);
            }
            System.out.print("\n");
        }
    }
}
