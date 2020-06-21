#include <bits/stdc++.h>

using namespace std;

int ncr[32][32];

int solve(int n) {
    int zeroes = 0, ones = 0, numDigits = -1;
    int ans = 0;
    for (int i = 31; i >= 0; i--) {
        if (n & (1 << i)) {
            if (numDigits == -1) {
                numDigits = i+1;
                if (__builtin_popcount(n) <= (numDigits)/2) ans++;
            }

            // let's make this a zero
            if (ones == 0) {
                // special case
                for (int j = i; j >= 0; j--) {
                    for (int k = (j+1)/2; k <= j-1; k++) {
                        ans += ncr[j-1][k];
                    }
                }
            } else {
                int neededZeroes = (numDigits+1)/2 - zeroes - 1;
                int digitsRemaining = i;
                for (int j = max(neededZeroes, 0); j <= digitsRemaining; j++) {
                    ans += ncr[digitsRemaining][j];
                }
            }

            ones++;
        } else {
            if (numDigits != -1) zeroes++;
        }
    }
    return ans;
}

int main() {
    int a, b; cin >> a >> b;

    for (int i = 0; i < 32; i++) for (int j = 0; j < 32; j++) ncr[i][j] = 0;
    ncr[0][0] = 1;
    for (int i = 1; i < 32; i++) {
        for (int j = 0; j <= i; j++) {
            ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
        }
    }

    /*
    int ans = 0;
    for (int i = a; i <= b; i++) {
        int ct = 0;
        while ((1<<ct)<=i)ct++;
        if (__builtin_popcount(i) <= ct/2) ans++;
    }
    cout << ans << endl;
    */

    cout << solve(b) - solve(a-1) << endl;

    return 0;
}
