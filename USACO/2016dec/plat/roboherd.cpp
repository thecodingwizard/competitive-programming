/*
 * same solution as editorial
 *
 * If we know the maximum cost we have to pay for a robot, we can construct the answer
 * in linear time:
 * - complete search with recursion, prune by exiting early if not enough money to spend
 * - greedily construct any robot that costs less than equal to (maximum-1); the remaining
 *   robots must all cost maximum. Note that we can't greedily construct robots that
 *   cost exactly maximum since that may yield WA (may not be optimal).
 * 
 * To find maximum cost, we can just binary search and check if we have enough robots.
 * Though 1e13 looks big, we can still binary search it in time
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

int n, k; 
vector<vector<int>> A;

int numModels = 0;
ll amountSaved = 0;
ll maxCost = 0;
void search(int idx, ll moneyLeft) {
    if (numModels >= k) return;
    if (idx == n) {
        numModels++;
        amountSaved += moneyLeft + 1;
        return;
    }
    if (moneyLeft < A[idx][0]) {
        // speed up by stopping the search
        search(n, moneyLeft);
        return;
    }
    // option 1: just use the base model
    search(idx+1, moneyLeft);
    // option 2: use something more expensive
    for (auto x : A[idx]) {
        if (x <= moneyLeft) {
            search(idx+1, moneyLeft-x);
        } else {
            break;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    freopen("roboherd.in", "r", stdin);
    freopen("roboherd.out", "w", stdout);

    cin >> n >> k;
    ll baseCost = 0;
    int actualN = 0;
    F0R(i, n) {
        int x; cin >> x;
        vector<int> B;
        F0R(j, x) {
            int y; cin >> y; B.pb(y);
        }
        sort(all(B));
        baseCost += B[0];
        FOR(j, 1, sz(B)) B[j] -= B[0];
        B.erase(B.begin());
        if (!B.empty()) {
            actualN++;
            A.pb(B);
        }
    }
    n = actualN;
    sort(all(A));

    ll lo = baseCost, hi = 1e13+1;
    ll upperBound = baseCost;
    while (lo < hi) {
        numModels = 0;
        ll mid = (lo+hi)/2;
        search(0, mid-baseCost);
        if (numModels >= k) {
            hi = mid;
            upperBound = mid;
        } else {
            lo = mid + 1;
        }
    }

    numModels = 0;
    maxCost = upperBound;
    amountSaved = 0;
    search(0, upperBound-baseCost-1);
    cout << (upperBound)*k-amountSaved << endl;

    return 0;
}
