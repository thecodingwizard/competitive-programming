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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef vector<int> vi;

int main() {
    int L[100000], L_id[100000], A[100000], P[100000], n = 0, x, lis = 0, lis_end = 0;
    while (cin >> x) A[n++] = x;

    for (int i = 0; i < n; i++) {
        int pos = lower_bound(L, L+lis, A[i]) - L;
        L[pos] = A[i];
        L_id[pos] = i;
        P[i] = pos ? L_id[pos - 1] : -1;
        if (pos + 1 >= lis) {
            lis = pos + 1;
            lis_end = i;
        }
    }

    cout << lis << endl << "-" << endl;

    stack<int> s;
    for (x = lis_end; P[x] != -1; x = P[x]) s.push(A[x]);
    s.push(A[x]);
    for (; !s.empty(); s.pop()) cout << s.top() << endl;

    return 0;
}
