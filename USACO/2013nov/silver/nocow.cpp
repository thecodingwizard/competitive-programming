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

using namespace std;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("nocow.in", "r", stdin);
    freopen("nocow.out", "w", stdout);

    int n, k; cin >> n >> k;
    set<string> words[n+100];
    vector<string> toSkip[n];
    int wordCt = 0;
    F0R(i, n) {
        string word; cin >> word >> word >> word >> word;
        wordCt = 0;
        while (cin >> word && word != "cow.") {
            words[wordCt++].insert(word);
            toSkip[i].push_back(word);
        }
    }
    int val[wordCt];
    int runningProduct = 1;
    F0Rd(i, wordCt) {
        val[i] = runningProduct;
        runningProduct *= words[i].size();
    }
    int toSkipPositions[n];
    F0R(i, n) {
        int position = 1;
        F0R (j, toSkip[i].size()) {
            position += val[j]*distance(words[j].begin(), words[j].find(toSkip[i][j]));
        }
        toSkipPositions[i] = position;
    }
    sort(toSkipPositions, toSkipPositions + n);
    F0R(i, n) {
        if (toSkipPositions[i] <= k) k++;
        else break;
    }

    vector<string> ans;
    k--;
    F0R(i, wordCt) {
        int idx = k/val[i];
        k %= val[i];
        ans.push_back(*next(words[i].begin(), idx));
    }

    bool first = true;
    for (string s : ans) {
        if (first) first = false;
        else cout << " ";
        cout << s;
    }
    cout << endl;

    return 0;
}
