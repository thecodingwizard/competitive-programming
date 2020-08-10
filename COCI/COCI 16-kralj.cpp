/*
 * For the 40% case: We basically need to assign one elf to each dwarf. We do this
 * greedily: If we can beat the dwarf, we do so with the weakest elf possible.
 * Otherwise, we send our weakest elf and lose. We can do this in nlogn with a multiset.
 *
 * To solve the remaining 60%, we just need to find a starting location such that
 * we can fill in all the seats with elves in order, without having to "skip"
 * a seat and come back to it later. This is similar to the USACO circular barn problem,
 * and it's guaranteed that such a location exists. We can find this location in O(n).
 *
 * We'll pick any one location that satisfies the above, and then run the same greedy
 * algorithm. We maintain a set of elves that can be sent to the next seat,
 * and then we greedily pick one to send.
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<int> adversaries[n];
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        adversaries[x-1].push_back(i);
    }
    int D[n], E[n];
    for (int i = 0; i < n; i++) cin >> D[i];
    for (int i = 0; i < n; i++) cin >> E[i];

    int ctr = 0;
    for (int i = 0; i < n; i++) {
        ctr = max(0, ctr - 1 + (int)adversaries[i].size());
    }
    int startIdx = -1;
    for (int i = 0; i < n; i++) {
        if (ctr == 0) {
            startIdx = i;
            break;
        }
        ctr = ctr - 1 + (int)adversaries[i].size();
        assert(ctr >= 0);
    }

    multiset<int> elves;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        int idx = (startIdx + i) % n;
        for (int elf : adversaries[idx]) {
            elves.insert(E[elf]);
        }
        auto it = elves.upper_bound(D[idx]);
        if (it == elves.end()) {
            elves.erase(elves.begin());
        } else {
            elves.erase(it);
            ans++;
        }
    }

    cout << ans << "\n";

    return 0;
}
