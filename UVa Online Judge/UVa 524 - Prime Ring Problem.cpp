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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
typedef vector<int> vi;

bool isPrime(int num){
    bool flag=true;
    for(int i = 2; i <= num / 2; i++) {
        if(num % i == 0) {
            flag = false;
            break;
        }
    }
    return flag;
}

int ring[16], N;
int digits[16];

bool check(int a, int b) {
    if (a == -1 || b == -1) return true;
    return isPrime(a + b);
}

void recurse(int i) {
    if (i == N) {
        if (!check(ring[N - 1], ring[0])) return;
        for (int x = 0; x < N; x++) {
            if (x > 0) cout << " ";
            cout << ring[x];
        }
        cout << endl;
    } else {
        for (int x = 0; x < N; x++) {
            if (i == 0 && digits[x] != 1) continue;
            if (digits[x] != -1) {
                if (i == 0 || check(digits[x], ring[i - 1])) {
                    ring[i] = digits[x];
                    digits[x] = -1;
                    recurse(i + 1);
                    digits[x] = x + 1;
                }
            }
        }
    }
}

int main() {
    int i = 1;
    while (cin >> N) {
        if (i > 1) cout << endl;
        for (int x = 0; x < 16; x++) {
            digits[x] = x + 1;
            ring[x] = -1;
        }
        cout << "Case " << i++ << ":" << endl;
        recurse(0);
    }
    return 0;
}