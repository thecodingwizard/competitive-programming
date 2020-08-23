/*
 * There are three cases:
 * Case 1: exact length
 * Case 2: some prefix of directories + symlink + some suffix to file
 * Case 3: dist to file + constant*(place symlink pointing to a parent directory of file)
 *
 * The first case can be handled by DFS
 *
 * For the second case, we can generate all prefix lengths and insert into set,
 * this takes O(N^2). Then, for every file, we just traverse up its parent
 * tree and try every suffix. This takes O(N) for every file which is fast enough
 *
 * For the third case, as we DFS into a directory, we add each subdirectory
 * (recursively) into a set (I used array for speed). When we leave, we'll
 * remove each subdirectory. This is O(N^2) since each pair is only added/removed once
 *
 * Then, when we're checking the file, we want to check if there is some
 * divisor of (k - dist to file) in the set. We can do this in sqrt time with brute force
 */

#include <bits/stdc++.h>

using namespace std;

int n, m, k, s; 
int dirLen[3001];
vector<int> subdirs[3001];
vector<int> dirfiles[3001];
int fileLen[3001];
bool ans[3001];
set<int> prefixLengths;

void dfsPrefixes(int u, int d) {
    prefixLengths.insert(d);
    for (int dir : subdirs[u]) {
        dfsPrefixes(dir, d + dirLen[dir]);
    }
}

vector<int> prefixLenStack;
int numCaseThreeLengths[1000001];

void dfsCaseThree(int u, int d, int v) {
    if (d + s > 1000000) return;
    numCaseThreeLengths[d+s] += v;

    for (int sub : subdirs[u]) {
        dfsCaseThree(sub, d + dirLen[sub], v);
    }
}

void dfs(int u, int d) {
    prefixLenStack.push_back(d);

    dfsCaseThree(u, 0, 1);

    for (int f : dirfiles[u]) {
        int totLen = fileLen[f] + d;

        // case 1
        if (totLen == k) ans[f] = true;

        // case 2
        for (int pfx : prefixLenStack) {
            int suffix = totLen - pfx + s;
            int want = k - suffix;
            if (prefixLengths.count(want)) ans[f] = true;
        }

        // case 3
        int want = k - totLen;
        if (want > 0) {
            for (int i = 1; i*i <= want; i++) {
                if (want % i == 0) {
                    if (numCaseThreeLengths[want/i] > 0) ans[f] = true;
                    if (numCaseThreeLengths[i] > 0) ans[f] = true;
                }
            }
        }
    }

    for (int sub : subdirs[u]) {
        dfs(sub, d + dirLen[sub]);
    }

    dfsCaseThree(u, 0, -1);

    prefixLenStack.pop_back();
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    cin >> n >> m >> k >> s; s++;
    for (int i = 1; i <= n; i++) {
        int p, l; cin >> p >> l;
        dirLen[i] = l+1;
        subdirs[p].push_back(i);
    }
    for (int i = 0; i < m; i++) {
        int p, l; cin >> p >> l;
        fileLen[i] = l+1;
        dirfiles[p].push_back(i);
    }

    // generate prefixes
    dfsPrefixes(0, 0);

    dfs(0, 0);

    for (int i = 0; i < m; i++) {
        if (ans[i]) cout << "YES" << "\n";
        else cout << "NO" << "\n";
    }
    
    return 0;
}
