/*
 * Define ct[i] = # of starting numbers that can be converted to i with exactly two bit flips
 *
 * Compute ct[i] for all i, can do this in O(n*20*20)
 *
 * Then, for every number i, we do ans += ct[(flip exactly two bits of i)] for all
 * possible flips. We overcounted, so we need to:
 *
 * - Subtract one for every instance of the number i in the input
 * - For every number in the input that differs by exactly two bits, we need to subtract 2*18
 *   - this is because they may make the same number by flipping one of the different bits, and then flipping one of their same bits (easiest if you draw it out: 0011 and 0101)
 * - We will overcount at the end by (4 choose 2) = 6, so divide final ans by 6
 *
 * Be careful, there are duplicate numbers in the input...
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("aiacubiti.in", "r", stdin);
    freopen("aiacubiti.out", "w", stdout);
    
    cin.tie(0); ios_base::sync_with_stdio(false);

    //mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

    int n; cin >> n;
    int A[n]; for (int i = 0; i < n; i++) cin >> A[i];
    /*
    int n = 100000; // cin >> n;
    int A[n]; for (int i = 0; i < n; i++) A[i] = rng()%(1<<20); // cin >> A[i];
    for (int i = 0; i < n; i++) cout << A[i] << " ";
    cout << endl;
    */
    int ct[(1 << 20)], dup[(1<<20)];
    for (int i = 0; i < (1 << 20); i++) ct[i] = dup[i] = 0;
    for (int i = 0; i < n; i++) dup[A[i]]++;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 20; j++) {
            for (int k = j+1; k < 20; k++) {
                int num = A[i] ^ (1 << j) ^ (1 << k);
                ct[num]++;
            }
        }
    }

    long long ans = 0;

    for (int i = 0; i < n; i++) {
        int x = dup[A[i]];
        for (int j = 0; j < 20; j++) {
            for (int k = j+1; k < 20; k++) {
                int num = A[i] ^ (1 << j) ^ (1 << k);
                ans += ct[num] - x;
                ans -= 2*18*dup[num];
            }
        }
    }
    /*
    long long ans2 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (__builtin_popcount(A[i]^A[j]) == 4) ans2++;
        }
    }
    cout << ans << " " << ans2 << endl;

    assert(ans % 12 == 0);
    assert(ans/12 == ans2);
    */

    cout << ans/12 << "\n";
}
