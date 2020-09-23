/*
 * Same as editorial, you can split the points into eight regions
 * sweep from left to right
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define inf 5000000000LL
#define ll long long
#define pb push_back
#define mp make_pair

pair<ll, ll> A[100000];
ll sums[10];
ll counts[10];
map<ll, vector<pair<int, ll>>> stuff;

// counts[0]*(s+x) - sums[0]
void addOne(ll l, ll r, int i) {
    stuff[l].pb(mp(1, A[i].s));
    stuff[r].pb(mp(-1, A[i].s));
}

// counts[1]*s - sums[1]
void addTwo(ll l, ll r, int i) {
    stuff[l].pb(mp(2, abs(A[i].f)));
    stuff[r].pb(mp(-2, abs(A[i].f)));
}

// sums[2] - (x-s)*counts[2]
void addThree(ll l, ll r, int i) {
    stuff[l].pb(mp(3, A[i].s));
    stuff[r].pb(mp(-3, A[i].s));
}

// counts[3]*s - sums[3]
void addFour(ll l, ll r, int i) {
    stuff[l].pb(mp(4, abs(A[i].f)));
    stuff[r].pb(mp(-4, abs(A[i].f)));
}

// sums[4]
void addFive(ll l, ll r, int i) {
    stuff[l].pb(mp(5, abs(A[i].f)));
    stuff[r].pb(mp(-5, abs(A[i].f)));
}

// sums[5] - count[5]*x + count[6]*x - sums[6]
void addSix(ll l, ll r, int i) {
    stuff[l].pb(mp(6, A[i].s));
    stuff[A[i].s].pb(mp(-6, A[i].s));
    stuff[A[i].s].pb(mp(7, A[i].s));
    stuff[r].pb(mp(-7, A[i].s));
}

void addSeven(ll l, ll r, int i) {
    addFive(l, r, i);
}

void addEight(ll l, ll r, int i) {
    addSix(l, r, i);
}

ll getCur(ll s, ll x) {
    ll sum = 0;

    // counts[0]*(s+x) - sums[0]
    sum += (counts[1]*(s+x)) - sums[1];

    // counts[1]*s - sums[1]
    sum += counts[2]*s - sums[2];

    // sums[2] - (x-s)*counts[2]
    sum += sums[3] - (x-s)*counts[3];

    // counts[3]*s - sums[3]
    sum += counts[4]*s - sums[4];

    // sums[4]
    sum += sums[5];

    // sums[5] - count[5]*x + count[6]*x - sums[6]
    sum += sums[6] - counts[6]*x + counts[7]*x - sums[7];

    //cout << counts[1] << " " << counts[2] << " " << counts[3] << " " << counts[4] << " " << counts[5] << " " << counts[6] << " " << counts[7] << endl;

    return sum;
}

int main() {
    ll n, s; cin >> n >> s;

    for (int i = 0; i < n; i++) {
        cin >> A[i].f >> A[i].s;
        A[i].s += 2e9+1;
    }

    for (int i = 0; i < n; i++) {
        ll rightDiag = A[i].s - abs(A[i].f);
        ll leftDiag = A[i].s + abs(A[i].f);
        if (abs(A[i].f) < s) {
            ll oneToFive = A[i].s-s;
            ll threeToSeven = A[i].s+s;
            addOne(oneToFive, rightDiag, i);
            if (A[i].f > 0) addTwo(rightDiag, leftDiag, i);
            else addFour(rightDiag, leftDiag, i);
            addThree(leftDiag, threeToSeven, i);
        }
        addFive(0, rightDiag, i);
        if (A[i].f > 0) addSix(rightDiag, leftDiag, i);
        else addEight(rightDiag, leftDiag, i);
        addSeven(leftDiag, inf, i);
    }

    ll best = -1;
    for (auto thing : stuff) {
        if (thing.f == inf) break;
        for (auto item : thing.s) {
            ll idx = item.f, val = item.s;
            if (idx > 0) {
                counts[idx]++;
                sums[idx] += val;
            } else {
                counts[-idx]--;
                sums[-idx] -= val;
            }
        }
        if (best == -1) best = getCur(s, thing.f);
        best = min(best, getCur(s, thing.f));
        //cout << getCur(s, thing.f) << " " << thing.f << endl;
    }
    cout << best << endl;

    return 0;
}
