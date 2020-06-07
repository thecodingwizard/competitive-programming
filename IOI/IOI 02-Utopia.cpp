/*
 * Solve up/down and left/right independently.
 *
 * Consider just left/right. If our sequence is alternating:
 * L R L R L R
 * Then we can sort the numbers we have in increasing order,
 * then alternate the signs of the numbers:
 * -1 +2 -3 +4 -5
 * and it will always work.
 *
 * If the sequence has duplicates:
 * L R L L L R R L
 * Then it's slightly more tricky. In this example, there are 3 duplicates.
 * What we can do is take the sorted array and set aside the three smallest
 * numbers. Then, whenever we encounter a duplicate, we take the largest
 * of the numbers we set aside, and we greedily see if we can use it to go
 * closer to zero without actually going past it. If we can, then go
 * towards zero. Otherwise, go away from zero. With some math, you can prove
 * that this always works.
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ii pair<int, int>
#define vi vector<int>
#define F0R(i, x) for (int i = 0; i < (x); i++)
#define pA first
#define pB second
#define pb push_back

int n; 

vi solve(int A[], vi X) {
    int dups = 0;

    for (int i = 0; i < n-1; i++) {
        if (X[i] == X[i+1]) dups++;
    }

    vi special;
    int idx = 0;
    for (; idx < dups; idx++) special.pb(A[idx]);

    vi ans;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (i>0 && X[i-1] == X[i]) {
            if (special.back() < abs(cur)) {
                ans.pb(-X[i]*special.back());
            } else {
                ans.pb(X[i]*special.back());
            }
            special.pop_back();
        } else {
            ans.pb(X[i]*A[idx++]);
        }
        cur += ans.back();
    }
    return ans;
}

int main() {
    cin >> n;
    
    int A[n], B[n];
    F0R(i, n) cin >> A[i];
    F0R(j, n) cin >> B[j];
    sort(A, A+n);
    sort(B, B+n);

    vi X, Y; // -1 = left, 1 = right
    F0R(i, n) {
        int a; cin >> a;
        if (a == 1) {
            X.pb(1); Y.pb(1);
        } else if (a == 2) {
            X.pb(-1); Y.pb(1);
        } else if (a == 3) {
            X.pb(-1); Y.pb(-1);
        } else {
            X.pb(1); Y.pb(-1);
        }
    }

    vi Xans = solve(A, X), Yans = solve(B, Y);
    for (int i = 0; i < n; i++) {
        cout << (Xans[i]>0?"+"+to_string(Xans[i]):to_string(Xans[i])) << " " << (Yans[i]>0?("+"+to_string(Yans[i])):to_string(Yans[i])) << endl;
    }

    return 0;
}
