/*
 * Greedy:
 * - Compress consecutive positive/negative elements so the array alternates
 *   between possitive and negative numbers
 * - Greedily start by taking all the positive elements in their own subarray
 * - While we have taken more than k subarrays, we try to eliminate one subarray at a time
 * - We can either get rid of one positive number subarray and merge it with its left/right negative neighbors, or we can join two positive number subarrays separated by a negative number, whichever will yield us the highest answer
 * - We can simulate this with sets
 */

#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second
using ll = long long;
#define ii pair<ll, int>
#define mp make_pair

struct node {
    ll v = 0;
    int i = -1;
    node *l, *r;
};

node A[300000];

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    int n, k; cin >> n >> k;
    ll cur = 0;
    int idx = 0;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        if ((cur > 0 && x < 0) || (cur < 0 && x > 0)) {
            A[idx++].v = cur;
            cur = 0;
        }
        cur += x;
    }
    if (cur != 0) A[idx++].v = cur;

    // first cost, second idx
    set<ii> giveUp;

    ll ans = 0;
    for (int i = 0; i < idx; i++) {
        if (i > 0) A[i].l = &A[i-1];
        else A[i].l = new node();
        if (i + 1 < idx) A[i].r = &A[i+1];
        else A[i].r = new node();
        A[i].i = i;
        //cerr << i << ": " << A[i].v << endl;
        if (A[i].v > 0) {
            giveUp.insert(mp(A[i].v, i));
            --k;
            ans += A[i].v;
        } else {
            if (i != 0 && i != idx-1) giveUp.insert(mp(-A[i].v, i));
        }
    }
    A[0].l->l = new node;
    A[0].l->r = &A[0];
    A[0].l->l->r = A[0].l;
    A[idx-1].r->l = &A[idx-1];
    A[idx-1].r->r = new node;
    A[idx-1].r->r->l = A[idx-1].l;

    while (k < 0) {
        if (giveUp.size() == 0) {
            cout << -1 << endl;
            return 0;
        }
        ii give = *giveUp.begin();
        //cerr << k << " " << ans << ". decision: " << give.f << ", " << give.s << endl;

        // delete this node
        ans -= give.f;
        int i = give.s;

        A[i].v += A[i].l->v + A[i].r->v;

        giveUp.erase(mp(abs(A[i].l->v), A[i].l->i));
        giveUp.erase(mp(abs(A[i].r->v), A[i].r->i));

        A[i].l->l->r = &A[i];
        A[i].r->r->l = &A[i];
        A[i].l = A[i].l->l;
        A[i].r = A[i].r->r;

        if (A[i].v > 0 || (A[i].l->v > 0 && A[i].r->v > 0)) giveUp.insert(mp(abs(A[i].v), i));

        giveUp.erase(give);
        k++;
    }

    cout << ans << endl;

    return 0;
}
