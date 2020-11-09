/*
Sort the input strings
For each query (A, B), we need to find the range [i, j] such that all input strings in that range has the prefix A
- To do this: either use a trie
- Or do some sketchy stuff with stacks. Sort the prefixes, then loop through the input strings, and keep track of the valid range of each prefix (look at implementation or just use tries)

Next, sort the input string reverse
We also need to find the range [x, y] such that all the input strings in that range has the suffix B

Each input string corresponds to (i, j) where i = its index in the first sorting, j = its index in the second sorting
We now have a series of 2DRQ [i, j] [x, y]
We can solve 2DRQ offline in nlogn
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define maxn 100000
int n, m; 
vector<pair<string, int>> A, B;
// query i corresponds to [inA[i], outA[i]] and [inB[i], outB[i]]
int inA[maxn], outA[maxn], inB[maxn], outB[maxn];
vector<int> points[maxn];
ii strings[maxn];
int qryAns[maxn];
// <<x, y>, <i, mult>>
// add mult*(query [x, y]) to qryAns[i]
vector<pair<ii, ii>> queries[maxn];

ii findRange(vector<pair<string, int>> &list, string s) {
    ii res = mp(-1, -1);
    for (int i = 0; i < (int)list.size(); i++) {
        if (list[i].f.rfind(s, 0) == 0) {
            res.s = i;
            if (res.f == -1) res.f = i;
        }
    }
    return res;
}

void calcInOut(vector<pair<string, int>> &A, vector<pair<string, int>> &prefixes, int* inA, int* outA) {
    int curPrefixIndex = 0;
    stack<int> activePrefixes;
    F0R(i, n) {
        while (!activePrefixes.empty() && A[i].f.rfind(prefixes[activePrefixes.top()].f, 0) != 0) {
            outA[prefixes[activePrefixes.top()].s] = i-1; activePrefixes.pop();
        }
        while (curPrefixIndex < m && A[i].f.rfind(prefixes[curPrefixIndex].f, 0) == 0) {
            inA[prefixes[curPrefixIndex].s] = i;
            activePrefixes.push(curPrefixIndex);
            curPrefixIndex++;
        }
        while (curPrefixIndex < m && prefixes[curPrefixIndex].f < A[i].f) {
            inA[prefixes[curPrefixIndex].s] = outA[prefixes[curPrefixIndex].s] = -1;
            curPrefixIndex++;
        }
        while (curPrefixIndex < m && A[i].f.rfind(prefixes[curPrefixIndex].f, 0) == 0) {
            inA[prefixes[curPrefixIndex].s] = i;
            activePrefixes.push(curPrefixIndex);
            curPrefixIndex++;
        }
    }
    while (!activePrefixes.empty()) {
        outA[prefixes[activePrefixes.top()].s] = n-1;
        activePrefixes.pop();
    }
}

int bit[maxn+10];
void upd(int k, int v) {
    k++;
    if (k <= 0) return;
    while (k <= n+5) {
        bit[k]+=v;
        k += k&-k;
    }
}
int qry(int k) {
    k++;
    if (k <= 0) return 0;
    int s = 0;
    while (k) {
        s += bit[k];
        k -= k&-k;
    }
    return s;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    F0R(i, n) {
        string s; cin >> s;
        A.pb(mp(s, i));
        reverse(all(s));
        B.pb(mp(s, i));
    }
    sort(all(A));
    sort(all(B));
    F0R(i, n) {
        strings[A[i].s].f = i;
        strings[B[i].s].s = i;
    }
    F0R(i, n) {
        //cout << "a point: " << strings[i].f << ", " << strings[i].s << endl;
        points[strings[i].f].pb(strings[i].s);
    }
    /*
    F0R(i, n) {
        cout << i << ": " << A[i].f << endl;
    }
    F0R(i, n) {
        cout << i << ": " << B[i].f << endl;
    }
    */

    vector<pair<string, string>> qryStrings;
    vector<pair<string, int>> prefixes, suffixes;
    F0R(i, m) {
        string a, b; cin >> a >> b; reverse(all(b));
        qryStrings.pb(mp(a, b));
        prefixes.pb(mp(a, i));
        suffixes.pb(mp(b, i));
    }
    sort(all(prefixes));
    sort(all(suffixes));

    calcInOut(A, prefixes, inA, outA);
    calcInOut(B, suffixes, inB, outB);

    /*
    for (auto x : prefixes) {
        int i = x.s;
        ii prefixRange = mp(inA[i], outA[i]); // findRange(0, a);
        ii suffixRange = mp(inB[i], outB[i]); // findRange(1, b);
        cout << qryStrings[i].f << "; " << qryStrings[i].s << ": [" << prefixRange.f << "," << prefixRange.s << "] and [" << suffixRange.f << "," << suffixRange.s << "]" << endl;
    }
    */

    F0R(i, m) {
        ii prefixRange = mp(inA[i], outA[i]); // findRange(0, a);
        ii suffixRange = mp(inB[i], outB[i]); // findRange(1, b);
        if (prefixRange.f-1 >= 0) queries[prefixRange.f-1].pb(mp(suffixRange, mp(i, -1)));
        if (prefixRange.s >= 0) queries[prefixRange.s].pb(mp(suffixRange, mp(i, 1)));
    }
    
    F0R(i, n) {
        for (int x : points[i]) {
            upd(x, 1);
            //cout << "updating " << x << endl;
        }
        for (auto x : queries[i]) {
            //cout << "adding " << x.s.s << "*[" << x.f.f << "," << x.f.s << "] to " << x.s.f << endl;
            qryAns[x.s.f] += x.s.s*(qry(x.f.s)-qry(x.f.f-1));
        }
    }
    F0R(i, m) cout << qryAns[i] << endl;

    return 0;
}
