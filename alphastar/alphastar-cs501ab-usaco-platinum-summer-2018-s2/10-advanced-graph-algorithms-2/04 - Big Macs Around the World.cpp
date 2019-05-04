/*
Big Macs Around the World
=========================

Bessie is studying her favorite subject, Macroeconomics, in cowllege.
For her final project, she will be presenting research on exchange
rates between countries around the world.

In order to make her presentation more lively, she would like to
show the relative prices of Big Macs around the world, despite their
rather unsavory contents. To illustrate, suppose that Bessie would
like to find smallest value of a Big Mac in a country given its
value in some initial country and exchange rates from which other
country's values can be calculated (as illustrated below):

* A Big Mac is worth 60 dollars in the United States

* The exchange rate from US dollars to Canadian dollars is 0.2
  Canadian dollars per US dollar

* The exchange rate from US dollars to British Pounds is 5.00 British
  Pounds per US Dollar

* The exchange rate from British Pounds to Canadian dollars is 0.5
  Canadian dollars per British Pound

* The exchange rate between Canadian dollars to US dollars is 5.00
  US dollars per Canadian dollar

and Bessie would like to find the smallest possible value of a Big
Mac in Canada that can be obtained by exchanging currencies. There
are two ways:

* Going from US dollars directly to Canada dollars would yield a
  burger worth 60.00 US dollars * 0.2 Canadian dollars / US dollar
  = 12.00 Canadian dollars

* Going from US dollars to British Pounds to Canadian dollars would
  yield a burger worth 60.00 US$ * 5.00 GBP / 1 US$ * 0.5 C$ / 1
  GBP = 150.00 C$ (Canadian dollars).

Bessie would choose the former option, since she would much rather
pay 12.00 Canadian dollars instead of 150.00 Canadian dollars for
a Big Mac in Canada.

Bessie has N (1 <= N <= 2,000) countries conveniently labeled 1 to
N that she would like to consider along with a list of M (1 <= M
<= 25,000) exchange rates e_ij (0.1 < e_ij <= 10), each between
countries i and j (1 <= i <= N; 1 <= j <= N).

Given the value V (1 <= V <= 1,000,000,000,000), which is not
necessarily an integer, of the Big Mac in her starting country A
(1 <= A <= N), help her find the smallest possible value of a Big
Mac in country B (1 <= B <= N; B != A) after a series of currency
conversions. If there is no minimum, output 0.

It is guaranteed that the answer is, if not 0, between 1 and 10^15.

It is also guaranteed that, for any country's currency, it is
possible to get to any other country's currency.

PROBLEM NAME: bigmac

INPUT FORMAT:

* Line 1: Five space-separated numbers: N, M, V, A, B

* Lines 2..M+1: Three space-separated numbers: i, j, e_ij

SAMPLE INPUT:

3 4 60 1 2
1 2 0.2
1 3 5
3 2 0.5
2 1 5

OUTPUT FORMAT:

* Line 1: A single positive number, only the integer part of the price of the Big Mac.
        If there is no minimum, output 0.

SAMPLE OUTPUT:

12
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
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LL_INF 0xfffffffffffffffLL
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    double v;
    int n, m, a, b; cin >> n >> m >> v >> a >> b;
    a--; b--;
    vector<vector<pair<int, double>>> adjList; adjList.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        double w; cin >> a >> b >> w;
        adjList[--a].push_back(mp(--b, w));
    }

    // Bellman Ford routine
    double dist[2001];
    for (int i = 0; i < n; i++) dist[i] = LL_INF;
    dist[a] = v;
    for (int i = 1; i < n; i++)  {
        for (int u = 0; u < n; u++) {
            for (pair<int, double> child : adjList[u]) {
                if (dist[u] == LL_INF) continue;
                if (dist[u] * child.B < dist[child.A]) dist[child.A] = dist[u] * child.B;
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (pair<int, double> child : adjList[u]) {
            if (dist[u] == LL_INF) continue;
            if ((dist[child.A] - dist[u] * child.B) > 1e-3) {
                cout << 0 << endl;
                return 0;
            }
        }
    }

    cout << (long long) floor(dist[b]) << endl;
    return 0;
}
