/*
 * Same as editorial: Note that the answer is either:
 * - A single number
 * - A long line of just ones
 * - A long line of just ones and one two somewhere in the middle
 *
 * You can show that one of these three is always optimal.
 *
 * My implemenation is very messy...
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n; 
ll A[1000000];
vector<int> adj[1000000];
ll num = 100000000000;
ll denom = 1;

int memoMaxOnesInLine[1000000];
int maxOnesInLine(int u, int p) {
    if (memoMaxOnesInLine[u] != -1) return memoMaxOnesInLine[u];
    if (A[u] != 1) return 0;
    int ans = 1;
    for (int v : adj[u]) {
        if (v != p) ans = max(ans, 1 + maxOnesInLine(v, u));
    }
    return memoMaxOnesInLine[u] = ans;
}

int maxOnesOnly(int u, int p) {
    int best = 0;
    if (A[u] == 1) {
        vector<int> childrenOnesCount;
        for (int v : adj[u]) {
            if (v != p) {
                childrenOnesCount.push_back(maxOnesInLine(v, u));
            }
        }
        sort(childrenOnesCount.begin(), childrenOnesCount.end());
        best = 1;
        if (childrenOnesCount.size()>=1) best = childrenOnesCount[childrenOnesCount.size()-1] + 1;
        if (childrenOnesCount.size()>=2) best += childrenOnesCount[childrenOnesCount.size()-2];
    }
    for (int v : adj[u]) {
        if (v != p) {
            best = max(best, maxOnesOnly(v, u));
        }
    }
    return best;
}

int maxOnesWithTwo(int u, int p, int numOnesFromParent) {
    int best = 0;
    int parentOnes = 0;
    vector<int> childrenOnesCount;
    for (int v : adj[u]) {
        if (v != p) {
            childrenOnesCount.push_back(maxOnesInLine(v, u));
        }
    }
    childrenOnesCount.push_back(numOnesFromParent);
    childrenOnesCount.push_back(0);
    sort(childrenOnesCount.begin(), childrenOnesCount.end());
    if (A[u] == 2) {
        best = childrenOnesCount[childrenOnesCount.size()-1] + childrenOnesCount[childrenOnesCount.size()-2] + 1;
    } else if (A[u] == 1) {
        parentOnes = 1 + numOnesFromParent;
        parentOnes = max(parentOnes, childrenOnesCount.back() + 1);
    }
    for (int v : adj[u]) {
        // warning: parentOnes will be wrong for one node...
        if (v != p) {
            if (childrenOnesCount.back() != childrenOnesCount[childrenOnesCount.size()-2]) {
                if (maxOnesInLine(v, u) == childrenOnesCount.back() && A[u] == 1) {
                    best = max(best, maxOnesWithTwo(v, u, max(numOnesFromParent+1, childrenOnesCount[childrenOnesCount.size()-2]+1)));
                } else {
                    best = max(best, maxOnesWithTwo(v, u, parentOnes));
                }
            } else {
                best = max(best, maxOnesWithTwo(v, u, parentOnes));
            }
        }
    }
    return best;
}

int main() {
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < n; i++) cin >> A[i];

    num = A[0];
    for (int i = 0; i < n; i++) {
        num = min(num, A[i]);
    }

    for (int i = 0; i < n; i++) {
        memoMaxOnesInLine[i] = -1;
    }

    // case 1: all ones
    int numOnes = maxOnesOnly(0, 0);

    // case 2: one two
    int numOnesWithTwo = maxOnesWithTwo(0, 0, 0);

    if (numOnes==0 || 1.0/numOnes > num) {
        if (numOnesWithTwo==0 || 2.0/numOnesWithTwo > num) {
            cout << num << "/" << 1 << endl;
        } else {
            if (numOnesWithTwo%2==0) {
                cout << "1/" << numOnesWithTwo/2 << endl;
            } else {
                cout << "2/" << numOnesWithTwo << endl;
            }
        }
    } else {
        if (numOnesWithTwo==0 || 2.0/numOnesWithTwo > 1.0/numOnes) {
            cout << "1/" << numOnes << endl;
        } else {
            if (numOnesWithTwo%2==0) {
                cout << "1/" << numOnesWithTwo/2 << endl;
            } else {
                cout << "2/" << numOnesWithTwo << endl;
            }
        }
    }

    return 0;
}
