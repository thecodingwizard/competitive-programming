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

int n;
vi children[100001];
bool isFile[100001];
int filesCt = 0;
int numFiles[100001];
ll nameLength[100001];
ll length[100001];
ll best = LL_INF;

ll dfsLength(int node, ll pathLength) {
    length[node] = pathLength + nameLength[node];
    for (int child : children[node]) dfsLength(child, length[node]);
}

int dfsFiles(int node) {
    if (isFile[node]) return 1;
    if (numFiles[node] != -1) return numFiles[node];
    int ct = 0;
    for (int child : children[node]) ct += dfsFiles(child);
    return numFiles[node] = ct;
}

void dfs(int node, ll dist) {
    best = min(best, dist);
    for (int child : children[node]) {
        if (isFile[child]) continue;
        ll newDist = dist - nameLength[child]*numFiles[child] + 3*(filesCt-numFiles[child]);
        dfs(child, newDist);
    }
}

int main() {
    freopen("dirtraverse.in", "r", stdin);
    freopen("dirtraverse.out", "w", stdout);

    cin >> n;
    F0R(i, n) {
        string name; int childrenCt; cin >> name >> childrenCt;
        nameLength[i] = name.length();
        F0R(j, childrenCt) {
            int x; cin >> x; x--;
            children[i].push_back(x);
        }
        isFile[i] = childrenCt == 0;
        if (isFile[i]) filesCt++;
        if (!isFile[i]) nameLength[i]++; // slash
    }
    nameLength[0] = 0;
    dfsLength(0, 0);
    ll initLength = 0;
    F0R(i, n) if (isFile[i]) initLength += length[i];
    best = initLength;
    F0R(i, n+1) numFiles[i] = -1;
    dfsFiles(0);
    dfs(0, initLength);
    cout << best << endl;

    return 0;
}
