/*
ID: nathan.18
TASK: sprime
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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

ofstream fout("sprime.out");
ifstream fin("sprime.in");

int n;

bool isPrime(int n) {
    if (n == 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i*i <= n; i += 2) if (n % i == 0) return false;
    return true;
}

void run(int num, int idx) {
    if (idx == n) {
        fout << num << endl;
        return;
    }
    for (int i = 1; i < 10; i++) {
        int newNum = num*10+i;
        if (isPrime(newNum)) {
            run(newNum, idx+1);
        }
    }
}

int main() {
    fin >> n;
    run(0, 0);
    return 0;
}
