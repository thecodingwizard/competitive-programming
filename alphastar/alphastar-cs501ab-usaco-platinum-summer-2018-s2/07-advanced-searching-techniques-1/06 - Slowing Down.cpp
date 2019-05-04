/*
Slowing Down
============

Every day each of Farmer John's N (1 <= N <= 100,000) cows conveniently
numbered 1..N move from the barn to her private pasture. The pastures
are organized as a tree, with the barn being on pasture 1. Exactly
N-1 cow unidirectional paths connect the pastures; directly connected
pastures have exactly one path. Path i connects pastures A_i and
B_i (1 <= A_i <= N; 1 <= B_i <= N).

Cow i has a private pasture P_i (1 <= P_i <= N). The barn's small
door lets only one cow exit at a time; and the patient cows wait
until their predecessor arrives at her private pasture. First cow
1 exits and moves to pasture P_1. Then cow 2 exits and goes to
pasture P_2, and so on.

While cow i walks to P_i she might or might not pass through a
pasture that already contains an eating cow. When a cow is present
in a pasture, cow i walks slower than usual to prevent annoying her
friend.

Consider the following pasture network, where the number between
parentheses indicates the pastures' owner.

        1 (3)
       / \
  (1) 4   3 (5)
     / \
(2) 2   5 (4)

First, cow 1 walks to her pasture:

        1 (3)
       / \
  [1] 4*  3 (5)
     / \
(2) 2   5 (4)

When cow 2 moves to her pasture, she first passes into the barn's
pasture, pasture 1. Then she sneaks around cow 1 in pasture 4 before
arriving at her own pasture.

        1 (3)
       / \
  [1] 4*  3 (5)
     / \
[2] 2*  5 (4)

Cow 3 doesn't get far at all -- she lounges in the barn's pasture, #1.

        1* [3]
       / \
  [1] 4*  3 (5)
     / \
[2] 2*  5 (4)

Cow 4 must slow for pasture 1 and 4 on her way to pasture 5:

        1* [3]
       / \
  [1] 4*  3 (5)
     / \
[2] 2*  5* [4]

Cow 5 slows for cow 3 in pasture 1 and then enters her own private pasture:

        1* [3]
       / \
  [1] 4*  3*[5]
     / \
[2] 2*  5* [4]

FJ would like to know how many times each cow has to slow down.

PROBLEM NAME: slowdown

INPUT FORMAT:

* Line 1: Line 1 contains a single integer: N

* Lines 2..N: Line i+1 contains two space-separated integers: A_i and
        B_i

* Lines N+1..N+N: line N+i contains a single integer: P_i

SAMPLE INPUT:

5
1 4
5 4
1 3
2 4
4
2
1
5
3

OUTPUT FORMAT:

* Lines 1..N: Line i contains the number of times cow i has to slow
        down.

SAMPLE OUTPUT:

0
1
0
2
1
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
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

class FenwickTree {
private:
    vi ft;

public:
    FenwickTree() {}
    // initialization: n + 1 zeroes, ignore index 0
    FenwickTree(int n) { ft.assign(n + 1, 0); }

    int rsq(int b) {                                     // returns RSQ(1, b)
        int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
        return sum; }

    int rsq(int a, int b) {                              // returns RSQ(a, b)
        return rsq(b) - (a == 1 ? 0 : rsq(a - 1)); }

    // adjusts value of the k-th element by v (v can be +ve/inc or -ve/dec)
    void adjust(int k, int v) {                    // note: n = ft.size() - 1
        for (; k < (int)ft.size(); k += LSOne(k)) ft[k] += v; }
};

vector<vi> adjList(100000+10);
bool visited[100000+10];
FenwickTree ft = FenwickTree(100000+10);
int ans[100000+10];
int goal[100000 + 10];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;
    int cow = goal[node];
    ans[cow] = ft.rsq(cow);
    ft.adjust(cow, 1);
    for (int i : adjList[node]) {
        if (!visited[i]) dfs(i);
    }
    ft.adjust(cow, -1);
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        goal[x] = i + 1;
    }
    memset(visited, false, sizeof visited);
    dfs(1);
    for (int i = 1; i <= n; i++) cout << ans[i] << endl;
    return 0;
}
