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
#define LL_INF 4500000000000000000
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
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);

    int n, k; cin >> n >> k;
    int cows[n];
    map<int, int> breedCompression; int numBreeds = 0;
    for (int i = 0; i < n; i++) {
        cin >> cows[i];
        if (breedCompression.find(cows[i]) == breedCompression.end()) {
            breedCompression.insert(mp(cows[i], numBreeds++));
        }
        cows[i] = breedCompression[cows[i]];
    }
    int cowCount[numBreeds];
    int breedCt = 0;
    int leftPtr = 0;
    int ans = 0;
    memset(cowCount, 0, sizeof cowCount);
    for (int i = 0; i < n; i++) {
        cowCount[cows[i]]++;
        if (cowCount[cows[i]] == 1) {
            breedCt++;
        }
        while (breedCt > k + 1) {
            cowCount[cows[leftPtr++]]--;
            if (cowCount[cows[leftPtr - 1]] == 0) {
                breedCt--;
            }
        }
        ans = max(ans, cowCount[cows[i]]);
    }
    cout << ans << endl;
    return 0;
}
