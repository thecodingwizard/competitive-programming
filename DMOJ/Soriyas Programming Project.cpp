/*
 * NOTE: since DMOJ updated their judge time limits, the code below no longer passes in time :(
 * However, Benq's OP code still passes in time, though barely. I've pasted it before my code.
 * CDQ solution works fine though
 *
 * case 1 = ( < val, > pos )
 * case 2 = ( > val, < pos )
 * When adding number "val" at index "pos", we just have to sum the answers
 * to these two cases.
 *
 * Copy paste benq's OP 2D offline BIT :)
 *
 * Make sure to use \n instead of endl...
 */

/* BEGIN OP BENQ CODE */

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef double db; 
typedef string str; 

typedef pair<int,int> pi;
typedef pair<ll,ll> pl; 
typedef pair<db,db> pd; 

typedef vector<int> vi; 
typedef vector<ll> vl; 
typedef vector<db> vd; 
typedef vector<str> vs; 
typedef vector<pi> vpi;
typedef vector<pl> vpl; 
typedef vector<pd> vpd; 

#define mp make_pair
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend() 
#define rsz resize
#define ins insert 
#define ft front() 
#define bk back()
#define pf push_front 
#define pb push_back
#define eb emplace_back 
#define lb lower_bound 
#define ub upper_bound 

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define trav(a,x) for (auto& a: x)

const int MOD = 1e9+7; // 998244353;
const int MX = 2e5+5; 
const ll INF = 1e18; 
const ld PI = acos((ld)-1);
const int xd[4] = {1,0,-1,0}, yd[4] = {0,1,0,-1}; 
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

template<class T> bool ckmin(T& a, const T& b) { 
	return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; } 
int pct(int x) { return __builtin_popcount(x); } 
int bit(int x) { return 31-__builtin_clz(x); } // floor(log2(x)) 
int cdiv(int a, int b) { return a/b+!(a<0||a%b == 0); } // division of a by b rounded up, assumes b > 0 
int fstTrue(function<bool(int)> f, int lo, int hi) {
	hi ++; assert(lo <= hi); // assuming f is increasing
	while (lo < hi) { // find first index such that f is true 
		int mid = (lo+hi)/2; 
		f(mid) ? hi = mid : lo = mid+1; 
	} 
	return lo;
}

// INPUT
template<class A> void re(complex<A>& c);
template<class A, class B> void re(pair<A,B>& p);
template<class A> void re(vector<A>& v);
template<class A, size_t SZ> void re(array<A,SZ>& a);

template<class T> void re(T& x) { cin >> x; }
void re(db& d) { str t; re(t); d = stod(t); }
void re(ld& d) { str t; re(t); d = stold(t); }
template<class H, class... T> void re(H& h, T&... t) { re(h); re(t...); }

template<class A> void re(complex<A>& c) { A a,b; re(a,b); c = {a,b}; }
template<class A, class B> void re(pair<A,B>& p) { re(p.f,p.s); }
template<class A> void re(vector<A>& x) { trav(a,x) re(a); }
template<class A, size_t SZ> void re(array<A,SZ>& x) { trav(a,x) re(a); }

// TO_STRING
#define ts to_string
str ts(char c) { return str(1,c); }
str ts(bool b) { return b ? "true" : "false"; }
str ts(const char* s) { return (str)s; }
str ts(str s) { return s; }
template<class A> str ts(complex<A> c) { 
	stringstream ss; ss << c; return ss.str(); }
str ts(vector<bool> v) { 
	str res = "{"; F0R(i,sz(v)) res += char('0'+v[i]);
	res += "}"; return res; }
template<size_t SZ> str ts(bitset<SZ> b) {
	str res = ""; F0R(i,SZ) res += char('0'+b[i]);
	return res; }
template<class A, class B> str ts(pair<A,B> p);
template<class T> str ts(T v) { // containers with begin(), end()
	bool fst = 1; str res = "{";
	for (const auto& x: v) {
		if (!fst) res += ", ";
		fst = 0; res += ts(x);
	}
	res += "}"; return res;
}
template<class A, class B> str ts(pair<A,B> p) {
	return "("+ts(p.f)+", "+ts(p.s)+")"; }

// OUTPUT
template<class A> void pr(A x) { cout << ts(x); }
template<class H, class... T> void pr(const H& h, const T&... t) { 
	pr(h); pr(t...); }
void ps() { pr("\n"); } // print w/ spaces
template<class H, class... T> void ps(const H& h, const T&... t) { 
	pr(h); if (sizeof...(t)) pr(" "); ps(t...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class H, class... T> void DBG(H h, T... t) {
	cerr << ts(h); if (sizeof...(t)) cerr << ", ";
	DBG(t...); }
#ifdef LOCAL // compile with -DLOCAL
#define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
#define dbg(...) 0
#endif

// FILE I/O
void setIn(string s) { freopen(s.c_str(),"r",stdin); }
void setOut(string s) { freopen(s.c_str(),"w",stdout); }
void unsyncIO() { ios_base::sync_with_stdio(0); cin.tie(0); }
void setIO(string s = "") {
	unsyncIO();
	// cin.exceptions(cin.failbit); 
	// throws exception when do smth illegal
	// ex. try to read letter into int
	if (sz(s)) { setIn(s+".in"), setOut(s+".out"); } // for USACO
}

/**
 * Description: point add and rectangle sum with offline 2D BIT. 
	* For each of the points to be added, $x\in (0,SZ)$ and $y\neq 0$.
 * Time: O(N\log^2 N)
 * Memory: O(N\log N)
 * Source: Own
 * Verification: 
 	* https://dmoj.ca/problem/occ19g4
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=722 (753 ms)
 	* http://www.usaco.org/index.php?page=viewproblem2&cpid=601 (679 ms)
 */

template<class T, int SZ> struct OffBIT2D { 
	bool mode = 0; // mode = 1 -> initialized
	vpi todo; // locations of updates to process
	int cnt[SZ], st[SZ];
	vi val; vector<T> bit; // store all BITs in single vector
	void init() { assert(!mode); mode = 1;
		int lst[SZ]; F0R(i,SZ) lst[i] = cnt[i] = 0;
		sort(all(todo),[](const pi& a, const pi& b) { 
			return a.s < b.s; });
		trav(t,todo) for (int x = t.f; x < SZ; x += x&-x) 
			if (lst[x] != t.s) lst[x] = t.s, cnt[x] ++;
		int sum = 0; F0R(i,SZ) lst[i] = 0, st[i] = (sum += cnt[i]);
		val.rsz(sum); bit.rsz(sum); reverse(all(todo));
		trav(t,todo) for (int x = t.f; x < SZ; x += x&-x) 
			if (lst[x] != t.s) lst[x] = t.s, val[--st[x]] = t.s;
	}
	int rank(int y, int l, int r) {
		return ub(begin(val)+l,begin(val)+r,y)-begin(val)-l; }
	void UPD(int x, int y, T t) {
		for (y = rank(y,st[x],st[x]+cnt[x]); y <= cnt[x]; y += y&-y) 
			bit[st[x]+y-1] += t; }
	void upd(int x, int y, T t) { 
		if (!mode) todo.pb({x,y});
		else for (;x<SZ;x+=x&-x) UPD(x,y,t); }
	int QUERY(int x, int y) { T res = 0;
		for (y = rank(y,st[x],st[x]+cnt[x]); y; y -= y&-y) res += bit[st[x]+y-1];
		return res; }
	T query(int x, int y) { assert(mode);
		T res = 0; for (;x;x-=x&-x) res += QUERY(x,y);
		return res; }
	T query(int xl, int xr, int yl, int yr) { 
		return query(xr,yr)-query(xl-1,yr)
			-query(xr,yl-1)+query(xl-1,yl-1); }
};

OffBIT2D<int,500005> O;
int N;
vi a,p;

int main() {
	setIO(); re(N); a.rsz(N), p.rsz(N); re(a,p);
	//trav(t,a) t = N+1-t;
	F0R(i,N) O.upd(p[i],a[p[i]-1],1);
	O.init();
	ll ans = 0;
	F0R(i,N) {
		int x = a[p[i]-1];
		O.upd(p[i],x,1);
		int z = O.query(p[i]-1,x);
		ans += O.query(p[i]-1,N)-z;
		ans += O.query(N,x-1)-O.query(p[i],x-1);
		ps(ans);
	}
	// you should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

/* END OP BENQ CODE */

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

namespace FastIO {
	const int BSZ = 1<<15; ////// INPUT
	char ibuf[BSZ]; int ipos, ilen;
	char nc() { // next char
		if (ipos == ilen) {
			ipos = 0; ilen = fread(ibuf,1,BSZ,stdin);
			if (!ilen) return EOF;
		}
		return ibuf[ipos++];
	}
	void rs(str& x) { // read str
		char ch; while (isspace(ch = nc()));
		do { x += ch; } while (!isspace(ch = nc()) && ch != EOF);
	}
	template<class T> void ri(T& x) { // read int or ll
		char ch; int sgn = 1;
		while (!isdigit(ch = nc())) if (ch == '-') sgn *= -1;
		x = ch-'0'; while (isdigit(ch = nc())) x = x*10+(ch-'0');
		x *= sgn;
	}
	template<class T, class... Ts> void ri(T& t, Ts&... ts) { 
		ri(t); ri(ts...); } // read ints
	////// OUTPUT (call initO() at start)
	char obuf[BSZ], numBuf[100]; int opos;
	void flushOut() { fwrite(obuf,1,opos,stdout); opos = 0; }
	void wc(char c) { // write char
		if (opos == BSZ) flushOut();
		obuf[opos++] = c; }
	void ws(str s) { trav(c,s) wc(c); } // write str
	template<class T> void wi(T x, char after = '\0') { /// write int
		if (x < 0) wc('-'), x *= -1;
		int len = 0; for (;x>=10;x/=10) numBuf[len++] = '0'+(x%10);
		wc('0'+x); R0F(i,len) wc(numBuf[i]);
		if (after) wc(after);
	}
	void initO() { assert(atexit(flushOut) == 0); } /// auto-flush output
}

using namespace FastIO;

int n;
OffBIT2D<int, 500000> bit;
int A[500000]; 
int P[500000]; 

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

	ri(n);
    for (int i = 0; i < n; i++) ri(A[i]);
    for (int i = 0; i < n; i++) ri(P[i]);

    for (int i = 0; i < n; i++) {
        bit.upd(A[P[i]-1], P[i], 0);
    }
    bit.init();

    ll s = 0;
    for (int i = 0; i < n; i++) {
        s += bit.query(A[P[i]-1]+1, n, 1, P[i]) + bit.query(1, A[P[i]-1]-1, P[i], n);
        cout << s << "\n";
        bit.upd(A[P[i]-1], P[i], 1);
    }
}
