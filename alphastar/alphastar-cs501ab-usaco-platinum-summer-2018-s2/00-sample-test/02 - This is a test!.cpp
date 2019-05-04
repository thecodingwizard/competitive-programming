/*
This is a test!
============
Time limit  : 1 sec
Memory limit: 16 MB
-------------------

Given a integer N output "This is a test!" N times on screen.

PROGRAM NAME: test

INPUT FORMAT:

* Line 1: N

SAMPLE INPUT:

3

OUTPUT FORMAT:

* Line 1..N: Each line contains "This is a test!"

SAMPLE OUTPUT:

This is a test!
This is a test!
This is a test!

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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int main() {
    int n;
    cin >> n;
    while (n--) {
        cout << "This is a test!" << endl;
    }
    return 0;
}
