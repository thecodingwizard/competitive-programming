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

int main() {
    int t, n, nums[12];
    while (cin >> t >> n && (t || n)) {
        cout << "Sums of " << t << ":" << endl;
        for (int i = 0; i < n; i++) cin >> nums[i];
        set<string, greater<string>> solutions;
        for (int i = 0; i < (1 << 12); i++) {
            int sum = 0;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    sum += nums[j];
                }
            }
            if (sum == t) {
                string s;
                bool first = true;
                for (int j = 0; j < n; j++) {
                    if (i & (1 << j)) {
                        if (!first) {
                            s += "+";
                        }
                        first = false;
                        s += to_string(nums[j]);
                    }
                }
                solutions.insert(s);
            }
        }
        if (solutions.empty()) cout << "NONE" << endl;
        else {
            for (const string &s : solutions) {
                cout << s << endl;
            }
        }
    }
    return 0;
}