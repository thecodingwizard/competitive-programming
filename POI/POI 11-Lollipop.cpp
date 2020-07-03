/*
 * If we're given something like
 *
 * W???????
 *
 * Then every number k is possible as long as k is less than equal to the
 * total sum of the numbers. We can achieve a number k by 
 * starting from index 2 (one-indexed), and greedily taking more numbers
 * as long as we don't exceed k. Finally, we will take the beginning W
 * if needed. It can be shown that this greedy works.
 *
 * Now, consider TTW?????
 *
 * We can use the same greedy strategy and just add the remaining T's as
 * needed (though in this case sometimes we won't be able to satisfy a given k).
 *
 * We may need to "reverse" the input in case it's like TTTTTTW????WT
 * we want the first W to come as soon as possible.
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);

    int n, m; cin >> n >> m;
    string s; cin >> s;

    int d1, d2;
    for (d1 = 0; d1 < n; d1++) {
        if (s[d1] == 'W') break;
    }
    for (d2 = n-1; d2 >= 0; d2--) {
        if (s[d2] == 'W') break;
    }
    bool rev = false;
    if (d1 > n-1-d2) {
        reverse(s.begin(), s.end());
        rev = true;
    }

    int numTwos = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'W') break;
        numTwos++;
    }
    int PS[n]; PS[0] = 0; // dumb edge case where n=1
    for (int i = numTwos+1; i < n; i++) {
        if (i>=n)break; // dumb edge case where n=1
        PS[i] = (i!=numTwos+1?PS[i-1]:0) + (s[i] == 'W' ? 1 : 2);
        //cout << "PS[" << i << "] = " << PS[i] << endl;
    }

    for (int i = 0; i < m; i++) {
        int k; cin >> k;

        if (numTwos == n) {
            if (k%2==1 || k>2*n) cout << "NIE" << "\n";
            else {
                cout << 1 << " " << k/2 << "\n";
            }
        } else {
            if (k > PS[n-1]+1) {
                int newK = k - PS[n-1] - 1;
                if (newK&1) {
                    cout << "NIE" << "\n";
                } else {
                    if (newK/2 <= numTwos) {
                        if (rev) cout << 1 << " " << n-numTwos+newK/2 << "\n";
                        else cout << numTwos+1-newK/2 << " " << n << "\n";
                    } else {
                        cout << "NIE" << "\n";
                    }
                }
            } else if (k == 1) {
                if (rev) cout << n-numTwos << " " << n-numTwos << "\n";
                else cout << numTwos + 1 << " " << numTwos + 1 << "\n";
            } else {
                int lo = numTwos+1, hi = n, mid, ans = numTwos+1;
                while (lo < hi) {
                    mid = (lo+hi)/2;
                    if (PS[mid] <= k) {
                        ans = mid;
                        lo = mid + 1;
                    } else {
                        hi = mid;
                    }
                }
                if (PS[ans] < k) {
                    if (rev) cout << n-ans << " " << n-numTwos << "\n";
                    else cout << numTwos+1 << " " << ans + 1 << "\n";
                } else {
                    if (rev) cout << n-ans << " " << n-numTwos-1 << "\n";
                    else cout << numTwos+2 << " " << ans + 1 << "\n";
                }
            }
        }
    }

    return 0;
}
