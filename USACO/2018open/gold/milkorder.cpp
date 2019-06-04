#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <unordered_set>

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n, m;
vi observations[50000];
int order[100000];
int degree[100000];
vi adjList[100000];

bool can(int x) {
    F0R(i, n) {
        adjList[i].clear();
        degree[i] = 0;
    }
    F0R(i, x) {
        int prevCow = -1;
        for (int cow : observations[i]) {
            if (prevCow != -1) {
                adjList[prevCow].push_back(cow);
                degree[cow]++;
            }
            prevCow = cow;
        }
    }
    priority_queue<int, vi, greater<int>> pq;
    int idx = 0;
    F0R(i, n) if (degree[i] == 0) pq.push(i);
    while (!pq.empty()) {
        int node = pq.top();
        order[idx++] = node; pq.pop();
        for (int child : adjList[node]) {
            degree[child]--;
            if (degree[child] == 0) pq.push(child);
        }
    }
    return idx == n;
}

int main() {
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);

    cin >> n >> m;
    F0R(i, m) {
        int num; cin >> num;
        F0R(j, num) {
            int x; cin >> x;
            observations[i].push_back(x-1);
        }
    }

    int lo = 0, hi = m+1, mid, ans;
    while (lo+1 < hi) {
        mid = (lo + hi)/2;
        if (can(mid)) {
            ans = mid;
            lo = mid;
        } else {
            hi = mid;
        }
    }

    can(ans);
    F0R(i, n) {
        if (i != 0) cout << " ";
        cout << order[i]+1;
    }
    cout << endl;

    return 0;
}
