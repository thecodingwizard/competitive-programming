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
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream infile(PROB + ".in");
    if (infile.good()) {
        freopen((PROB + ".in").c_str(), "r", stdin);
        freopen((PROB + ".out").c_str(), "w", stdout);
    }
}

/* ============================ */

vector<char> nodes;
vector<char> children[1000];
bool visited[1000];
int inDegree[1000];
vector<char> current;
bool hasOption = false;

void printOption() {
    hasOption = true;
    bool first = true;
    for (char c : current) {
        if (first) first = false;
        else cout << " ";
        cout << c;
    }
    cout << endl;
}

void toposort() {
    if (current.size() == nodes.size()) {
        printOption();
        return;
    }
    for (char node : nodes) {
        if (!visited[node] && inDegree[node] == 0) {
            current.pb(node);
            visited[node] = true;
            for (char child : children[node]) {
                inDegree[child]--;
            }
            toposort();
            visited[node] = false;
            for (char child : children[node]) {
                inDegree[child]++;
            }
            current.pop_back();
        }
    }
}

int main() {
    int cases; cin >> cases;
    cin.ignore();

    bool first = true;
    while (cases--) {
        if (first) first = false;
        else cout << endl;
        hasOption = false;
        nodes.clear();
        F0R(i, 1000) children[i].clear();
        SET(visited, false, 1000);
        SET(inDegree, 0, 1000);
        cin.ignore();
        string s;
        getline(cin, s);
        stringstream ss;
        ss << s;
        char c;
        while (ss >> c) {
            nodes.pb(c);
        }
        stringstream ss2;
        getline(cin, s);
        ss2 << s;
        string constraint;
        while (ss2 >> constraint) {
            children[constraint[0]].pb(constraint[2]);
            inDegree[constraint[2]]++;
        }

        SORT(nodes);
        toposort();

        if (!hasOption) {
            cout << "NO" << endl;
        }
    }

    return 0;
}