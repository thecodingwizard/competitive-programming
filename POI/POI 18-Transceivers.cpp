/*
 * Lazy seg tree where each node stores the sum of all the nodes in its range
 * For the lazy aspect, each node also stores the leftmost value that needs to be added
 * as well as the increment between x and x+1 inside its range.
 *
 * Adding a tower can then be split into two updates on the seg tree.
 *
 * I think (?) this is another video editorial: https://codeforces.com/blog/entry/78760
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

#define maxn 300000

ii tower[maxn];
int n, m; 

struct node {
    ll sum = 0, lval = 0, inc = 0;
} st[4*maxn];

void down(int p, int i, int j) {
    if (i != j && (st[p].lval != 0 || st[p].inc != 0)) {
        //cout << "down on " << i << ", " << j << " with lval = " << st[p].lval << " and " << st[p].inc << endl;
        st[p*2].lval += st[p].lval;
        st[p*2].inc += st[p].inc;
        ll len = (i+j)/2-i+1;
        st[p*2].sum += st[p].lval*len+st[p].inc*len*(len-1)/2;
        //cout << i << " " << (i+j)/2 << " is set to " << st[p*2].sum << endl;

        ll lvalchange = st[p].lval + st[p].inc*len;
        st[p*2+1].lval += lvalchange;
        st[p*2+1].inc += st[p].inc;
        len = (j-(i+j)/2);
        st[p*2+1].sum += lvalchange*len + st[p].inc*len*(len-1)/2;
        //cout << (i+j)/2+1 << " " << j << " is set to " << st[p*2+1].sum << endl;
    }
    st[p].inc = st[p].lval = 0;
}

void upd(int p, int i, int j, int l, int r, ll lVal, ll inc) {
    down(p, i, j);
    if (i > r || j < l) return;
    if (l <= i && j <= r) {
        st[p].lval = lVal+inc*(i-l);
        st[p].inc = inc;
        st[p].sum += (lVal+inc*(i-l))*(j-i+1);
        st[p].sum += inc*(j-i+1)*(j-i)/2;
        //cout << i << ", " << j << " is set to " << st[p].sum << endl;
        return;
    }
    upd(p*2, i, (i+j)/2, l, r, lVal, inc);
    upd(p*2+1, (i+j)/2+1, j, l, r, lVal, inc);
    st[p].sum = st[p*2].sum + st[p*2+1].sum;
}

ll qry(int p, int i, int j, int l, int r) {
    down(p, i, j);
    if (j < l || i > r) return 0;
    if (l <= i && j <= r) return st[p].sum;
    return qry(p*2, i, (i+j)/2, l, r) + qry(p*2+1, (i+j)/2+1, j, l, r);
}

void addTower(int x, ll mult) {
    ll s = tower[x].f, a = tower[x].s;
    ll d = s/a;
    upd(1, 0, n-1, x-d, x, s%a*mult, a*mult);
    upd(1, 0, n-1, x+1, x+d, (s-a)*mult, -a*mult);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    F0R(i, m) {
        char c; cin >> c;
        if (c == 'P') {
            int x, s, a; cin >> x >> s >> a; --x;
            tower[x] = mp(s, a);
            addTower(x, 1);
        } else if (c == 'U') {
            int x; cin >> x; --x;
            addTower(x, -1);
        } else {
            int x, y; cin >> x >> y; --x; --y;
            cout << qry(1, 0, n-1, x, y)/(y-x+1) << endl;
        }
    }

    return 0;
}
