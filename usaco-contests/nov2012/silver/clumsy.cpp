/* Clumsy Cows, Greedy */

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
#define LL_INF 4523372036854775807
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

ofstream fout("clumsy.out");
ifstream fin("clumsy.in");

int main() {
    int ct = 0, sum = 0;
    char c;
    while (fin >> c) {
        if (c == '(') sum++;
        else sum--;
        if (sum < 0) {
            ct++;
            sum = 1;
        }
    }
    fout << ct + sum/2 << endl;
    return 0;
}
