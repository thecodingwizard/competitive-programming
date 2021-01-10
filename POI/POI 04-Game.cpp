/*
 * This problem can be viewed as the nim staircase problem.
 *
 * You can treat every empty location as a "border" of the staircase, and the number
 * of discs in every contiguous section of discs bounded by two such "borders" would 
 * be considered the "value" of that particular staircase location.
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int m, n; cin >> m >> n;
    vector<int> A(n); F0R(i, n) cin >> A[i];
    sort(all(A));

    if (A.back() == m-1) {
        int ct = 1;
        int i = n-2;
        while (~i && A[i] == A[i+1]-1) {
            ct++;
            i--;
        }
        cout << ct << endl;
        return 0;
    }

    int nim_sum = 0;
    int encountered = 0;
    for (int i = n-1; ~i;) {
        int first = i, last = i;
        while (last-1>=0 && A[last-1]==A[last]-1) last--;
        
        int idx = m-2-A[first]-encountered;
        if (idx % 2 == 1) nim_sum ^= (first-last+1);

        //cout << "idx " << idx << " and " << (first-last+1) << endl;

        encountered += first-last+1;
        i = last-1;
    }

    if (nim_sum == 0) cout << 0 << endl;
    else {
        int ct = 0;

        encountered = 0;
        int prev_size = 0;
        for (int i = n-1; ~i;) {
            int first = i, last = i;
            while (last-1>=0 && A[last-1]==A[last]-1) last--;
            
            int idx = m-2-A[first]-encountered;

            //cout << "idx " << idx << " and " << (first-last+1) << endl;

            if (idx % 2 == 1 && first-last+1 >= (nim_sum^(first-last+1))) ct++;
            else if (idx % 2 == 0 && idx != 0) {
                if (first+1<n && A[first] == A[first+1]-2) {
                    if ((nim_sum^prev_size) <= first-last+1+prev_size && (nim_sum^prev_size) > prev_size)ct++;
                } else if (first-last+1 >= nim_sum) ct++;
            }

            prev_size = first-last+1;

            encountered += first-last+1;
            i = last-1;
        }
        cout << ct << endl;
    }

    return 0;
}
