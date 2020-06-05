/*
 * case 1 = ( < val, > pos )
 * case 2 = ( > val, < pos )
 * When adding number "val" at index "pos", we just have to sum the answers
 * to these two cases.
 *
 * Copy paste benq's OP 2D offline BIT :)
 *
 * Make sure to use \n instead of endl...
 */

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef double db; //
typedef string str; //
//
typedef pair<int,int> pi;
typedef pair<ll,ll> pl; //
typedef pair<db,db> pd; //
//
typedef vector<int> vi; 
typedef vector<ll> vl; //
typedef vector<db> vd; //
typedef vector<str> vs; //
typedef vector<pi> vpi;
typedef vector<pl> vpl; //
typedef vector<pd> vpd; //

#define mp make_pair
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend() //
#define rsz resize
#define ins insert //
#define ft front() //
#define bk back()
#define pf push_front //
#define pb push_back
#define eb emplace_back //
#define lb lower_bound //
#define ub upper_bound //

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353;
const int MX = 2e5+5; //
const ll INF = 1e18; //
const ld PI = acos((ld)-1);


template<class T, int SZ> struct OffBIT2D { 
	bool mode = 0; // mode = 1 -> initialized
	vpi todo;
	int cnt[SZ], st[SZ];
	vi val, bit;
	void init() {
		assert(!mode); mode = 1;
		int lst[SZ]; F0R(i,SZ) lst[i] = cnt[i] = 0;
		sort(all(todo),[](const pi& a, const pi& b) { 
			return a.s < b.s; });
		trav(t,todo) for (int x = t.f; x < SZ; x += x&-x) 
			if (lst[x] != t.s) lst[x] = t.s, cnt[x] ++;
		int sum = 0;
		F0R(i,SZ) { lst[i] = 0; st[i] = sum; sum += cnt[i]; }
		val.rsz(sum); bit.rsz(sum); // store BITs in single vector
		trav(t,todo) for (int x = t.f; x < SZ; x += x&-x) 
			if (lst[x] != t.s) lst[x] = t.s, val[st[x]++] = t.s;
	}
	int rank(int y, int l, int r) {
		return ub(begin(val)+l,begin(val)+r,y)-begin(val)-l; }
	void UPD(int x, int y, int t) {
		int z = st[x]-cnt[x]; // x-BIT = range from z to st[x]-1
		for (y = rank(y,z,st[x]); y <= cnt[x]; y += y&-y) 
			bit[z+y-1] += t;
	}
	void upd(int x, int y, int t) { 
		if (!mode) todo.pb({x,y});
		else for (;x<SZ;x+=x&-x) UPD(x,y,t); 
	}
	int QUERY(int x, int y) {
		int z = st[x]-cnt[x], res = 0;
		for (y = rank(y,z,st[x]); y; y -= y&-y) res += bit[z+y-1];
		return res;
	}
	int query(int x, int y) { 
		assert(mode);
		int res = 0; for (; x; x -= x&-x) res += QUERY(x,y);
		return res;
	}
	int query(int xl, int xr, int yl, int yr) { 
		return query(xr,yr)-query(xl-1,yr)
			-query(xr,yl-1)+query(xl-1,yl-1); }
};

int n;
OffBIT2D<int, 500000> bit;

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    cin >> n;
    int A[n]; for (int i = 0; i < n; i++) cin >> A[i];
    int P[n]; for (int i = 0; i < n; i++) cin >> P[i];

    for (int i = 0; i < n; i++) {
        bit.upd(A[P[i]-1], P[i], 0);
    }
    bit.init();

    ll s = 0;
    for (int i = 0; i < n; i++) {
        int p = P[i]-1;
        int v = A[p];
        p++;
        s += bit.query(v+1, n, 1, p) + bit.query(1, v-1, p, n);
        cout << s << "\n";
        bit.upd(v, p, 1);
    }
}
