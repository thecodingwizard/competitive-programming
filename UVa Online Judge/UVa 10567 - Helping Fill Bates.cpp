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

vector<int> characters[100];

struct compare {
    inline bool operator()(const int left, const int right) const {
        return left<=right;
    };
};

int main() {
    string s;
    cin >> s;
    int q;
    cin >> q;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        characters[c - 'A'].push_back(i);
    }

    compare c;
    while (q--) {
        cin >> s;
        int first = 0, last = -1;
        bool valid = true;
        for (int i = 0; i < s.length(); i++) {
            int idx = s[i] - 'A';
            auto it = lower_bound(characters[idx].begin(), characters[idx].end(), last, c);
            if (it == characters[idx].end()) {
                valid = false;
                break;
            } else {
                last = *it;
                if (i == 0) {
                    first = last;
                }
            }
        }

        if (valid) {
            cout << "Matched " << first << " " << last << endl;
        } else {
            cout << "Not matched" << endl;
        }
    }

    return 0;
}