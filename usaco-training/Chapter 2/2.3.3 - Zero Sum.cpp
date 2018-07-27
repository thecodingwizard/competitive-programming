/*
ID: nathan.18
TASK: zerosum
LANG: C++
*/

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

int n, curNum = 1, curTotal = 0, curSign = 1;
string curSequence = "";
vector<string> ans;

void dfs(int curIdx) {
    if (curIdx == n) {
        if (curTotal+curNum*curSign == 0) {
            ans.push_back(curSequence);
        }
        return;
    }
    int curNum2 = curNum, curTotal2 = curTotal, curSign2 = curSign;
    string curSequence2 = curSequence;
    // blank
    curSequence += " ";
    curNum = curNum*10 + curIdx+1;
    dfs(curIdx+1);
    curNum = curNum2;
    curSequence = curSequence2;
    // plus
    curSequence += "+";
    curTotal = curTotal + curNum*curSign;
    curSign = 1;
    curNum = curIdx+1;
    dfs(curIdx+1);
    curNum = curNum2;
    curSign = curSign2;
    curTotal = curTotal2;
    curSequence = curSequence2;
    // minus
    curSequence += "-";
    curTotal = curTotal + curNum*curSign;
    curSign = -1;
    curNum = curIdx+1;
    dfs(curIdx+1);
    curNum = curNum2;
    curSign = curSign2;
    curTotal = curTotal2;
    curSequence = curSequence2;
}

int main() {
    freopen("zerosum.in", "r", stdin);
    freopen("zerosum.out", "w", stdout);

    cin >> n;
    dfs(1);
    for (string s : ans) {
        cout << '1';
        FOR(i, 1, n) {
            cout << s[i-1] << i+1;
        }
        cout << endl;
    }

    return 0;
}
