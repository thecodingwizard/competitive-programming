/*
 * See: https://github.com/quangloc99/CompetitiveProgramming/blob/master/olympiad/JOISC/2019/naan.cpp
 * See: https://oj.uz/submission/133978
 *
 * Apparently greedily picking the person with minimal increase of nan works, but due to
 * precision errors cannot get full credit.
 *
 * For each person i, define array split[i][j] = where to split the nan such that
 * if person i takes all the nan from 0...split[i][j], then they will have happiness
 * equal to (j+1)*sum[i]/n.
 *
 * Essentially, the array split[i][] splits the nan into n pieces, where each piece
 * holds sum[i]/n happiness for the i'th person.
 *
 * Then, we can greedily take the person with the least split[i][0], followed by the person with
 * the least split[i][1], etc.
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long

// returns true if fraction a < fraction b
bool better(pair<ll, ll> a, pair<ll, ll> b) {
    return __int128(a.first)*b.second<__int128(a.second)*b.first;
}

pair<ll,ll> reduce(pair<ll, ll>a) {
    ll g = __gcd(a.first, a.second);
    return make_pair(a.first/g,a.second/g);
}

int main() {
    int n, l; cin >> n >> l;
    ll V[n][l];
    ll sum[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < l; j++) cin >> V[i][j];
        sum[i] = 0; for (int j = 0; j < l; j++) sum[i] += V[i][j];
    }
    pair<ll, ll> split[n][n];
    for (int i = 0; i < n; i++) {
        int cur = 0;
        ll want = 0;
        for (int j = 1; j < n; j++) {
            want += sum[i];
            while (cur < l && V[i][cur]*n <= want) {
                want -= V[i][cur]*n;
                cur++;
            }
            split[i][j] = reduce(make_pair((ll)cur*V[i][cur]*n+want, V[i][cur]*n));
            //cout << "split[" << i << "][" << j << "] = " << split[i][j].first << "/" << split[i][j].second << endl;
        }
    }
    bool taken[n]; for (int i = 0; i < n; i++) taken[i] = false;
    vector<int> permutation;
    for (int i = 1; i < n; i++) {
        int best = -1;
        for (int j = 0; j < n; j++) {
            if (taken[j]) continue;
            if (best == -1) {
                best = j;
            } else {
                if (better(split[j][i], split[best][i])) best = j;
            }
        }
        taken[best] = true;
        cout << split[best][i].first << " " << split[best][i].second << endl;
        permutation.push_back(best+1);
    }
    for (int j = 0; j < n; j++) if (!taken[j]) permutation.push_back(j+1);
    for (int x : permutation) cout << x << " ";
    cout << endl;
    return 0;
}
