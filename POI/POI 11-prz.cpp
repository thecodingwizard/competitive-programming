/*
 * The command b essentially lets you cyclically shift the first three numbers.
 *
 * The command a lets you cyclically shift the entire array.
 *
 * Together, you can essentially cyclically shift any three consecutive numbers
 * by moving the three numbers to the beginning of the array with a, shifting them
 * with b, and then moving everything back with a.
 *
 * We can sort the array by first finding the number 1, then using cyclic shifts
 * to move 1 to the very beginning of the array. Then we do the same thing for
 * the number 2, and so on. With this, we can sort the entire array except for
 * the last two numbers.
 *
 * If the last two numbers are already in the right order, great! Otherwise:
 *
 * If the length of the array is even, then we can just shift the entire array by
 * one, and then rerun the algorithm: 1 2 4 3 ==> 3 1 2 4 ==> (rerun) ==> 1 2 3 4
 *
 * If the length of the array is odd, then doing that doesn't work, and we're
 * unable to sort the array.
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

int n; 
vector<ii> ans;
vector<int> A;

void solve(int x) {
    int tgtIdx = x-1;
    int curIdx = find(all(A), x)-A.begin();

    //cout << "Solving " << x << ": " << endl;
    while (tgtIdx != curIdx) {
        int destIdx = max(curIdx - 2, tgtIdx);
        ans.pb(mp(1, n-destIdx));
        //cout << ans.back().s << "b" << endl;
        if (destIdx == curIdx - 2) {
            ans.pb(mp(0, 1));
            //cout << ans.back().s << "a" << endl;
            int tmp = A[curIdx];
            A[curIdx] = A[destIdx+1];
            A[destIdx+1] = A[destIdx];
            A[destIdx] = tmp;
        } else {
            assert(destIdx == curIdx - 1);
            ans.pb(mp(0, 2));
            //cout << ans.back().s << "a" << endl;
            int tmp = A[destIdx];
            A[destIdx] = A[curIdx];
            A[curIdx] = A[curIdx+1];
            A[curIdx+1] = tmp;
        }
        ans.pb(mp(1, destIdx));
        //cout << ans.back().s << "b" << endl;
        curIdx = destIdx;
    }
}

void process() {
    FOR(i, 1, n-1) {
        solve(i);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    F0R(i, n) {
        int x; cin >> x; A.pb(x);
    }

    process();

    if (A.back() != n) {
        if (n % 2 == 0) {
            ans.pb(mp(1, 1));
            A.insert(A.begin(), A.back());
            A.pop_back();
            process();
        } else {
            cout << "NIE DA SIE" << endl;
            return 0;
        }
    }

    vector<ii> realAns;
    ii cur = mp(-1, -1);
    for (auto x : ans) {
        if (cur.f == -1) cur = x;
        else {
            if (cur.f == x.f) {
                cur.s += x.s;
            } else {
                if (cur.f == 1) {
                    cur.s %= n;
                }
                if (cur.f == 0) {
                    cur.s %= 3;
                }
                if (cur.s == 0) {
                    if (!realAns.empty()) {
                        cur = realAns.back();
                        assert(cur.f == x.f);
                        realAns.pop_back();
                        cur.s += x.s;
                    } else {
                        cur = x;
                    }
                } else {
                    realAns.pb(cur);
                    cur = x;
                }
            }
        }
    }
    if (cur.f != -1) {
        cur.s %= n;
        if (cur.s != 0) realAns.pb(cur);
    }

    cout << realAns.size() << endl;
    for (auto x : realAns) cout << x.s << "ba"[x.f] << " ";
    cout << endl;

    return 0;
}
