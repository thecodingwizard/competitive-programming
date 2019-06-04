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
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    freopen("empty.in", "r", stdin);
    freopen("empty.out", "w", stdout);

    unsigned int n, k;
    cin >> n >> k;
    unsigned int x, y, a, b;
    auto * stalls = new unsigned int[3000001];
    memset(stalls, 0, sizeof stalls);
    for (int i = 0; i < k; i++) {
        cin >> x >> y >> a >> b;
        for (int j = 1; j <= y; j++) {
            unsigned int stall = ((a%n)*j+b)%n;
            stalls[stall] += x;
        }
    }
    unsigned int counter = 0;
    for (int i = 0; i < n; i++) {
        counter += stalls[i];
        if (counter > 0) counter--;
    }
    for (int i = 0; i < n; i++) {
        counter += stalls[i];
        if (counter > 0) counter--;
        else {
            cout << i;
            break;
        }
    }
    return 0;
}
