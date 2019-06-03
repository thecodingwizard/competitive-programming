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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
typedef vector<int> vi;

vi primes;
bool isPrime[1000001];

struct compare {
    inline bool operator()(const int left, const int right) const {
        return left<=right;
    };
};

int main() {

    memset(isPrime, true, sizeof(isPrime));
    isPrime[1] = false;
    for (int i = 2; i < 1000001; i++) {
        if (isPrime[i]) {
            for (int j = i*2; j < 1000001; j += i) {
                isPrime[j] = false;
            }
            primes.push_back(i);
        }
    }

    compare c;
    int n;
    int i = 1;
    while (cin >> n && n) {
        int sum = 0;
        for (int i = 0; i < primes.size(); i++) {
            int prime = primes[i];
            auto it = lower_bound(primes.begin(), primes.end(), n - prime, c);
            it--;
            if (*it < prime) break;
            sum += it - primes.begin() - i;
        }
        cout << "Case " << i++ << ": " << sum << endl;
    }

    return 0;
}