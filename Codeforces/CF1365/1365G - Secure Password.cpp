#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;

    vector<int> masks;
    for (int i = 0; i < (1 << 13); i++) {
        if (__builtin_popcount(i) == 6) masks.push_back(i);
    }

    long long res[13];
    for (int i = 0; i < 13; i++) {
        vector<int> ask;
        for (int j = 0; j < n; j++) {
            if (masks[j] & (1 << i)) {
                ask.push_back(j + 1);
            }
        }
        res[i] = 0;
        if (ask.size() == 0) continue;
        cout << "? " << ask.size();
        for (int x : ask) cout << " " << x;
        cout << endl;
        cin >> res[i];
    }

    cout << "!";
    for (int i = 0; i < n; i++) {
        long long ans = 0;
        for (int j = 0; j < 13; j++) {
            if (!(masks[i] & (1 << j))) ans |= res[j];
        }
        cout << " " << ans;
    }
    cout << endl;

    return 0;
}
