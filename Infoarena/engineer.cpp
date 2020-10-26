/*
 * Parallel binary search + BIT
 *
 * The time limit is ridiculously tight, so you basically can't use maps at all.
 * Instead of using 2D BIT, you have to use 1D bit and just brute force loop through
 * one dimension (no idea why this works but a 2D bit doesn't)
 */

#include <bits/stdc++.h>
 
using namespace std;
 
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
	void rs(string& x) { // read str
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
	void ws(string s) { for (auto &c : s) wc(c); } // write str
	template<class T> void wi(T x, char after = '\0') { /// write int
		if (x < 0) wc('-'), x *= -1;
		int len = 0; for (;x>=10;x/=10) numBuf[len++] = '0'+(x%10);
		wc('0'+x); for (int i = len-1; i; i--) wc(numBuf[i]);
		if (after) wc(after);
	}
	void initO() { assert(atexit(flushOut) == 0); } /// auto-flush output
}
 
using namespace FastIO;
 
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair
#define pb push_back
 
struct query {
    int x, y, a, b, k;
};
 
int n, m, q; 
int A[1100][1100];
int L[1000], R[1000];
vector<query> queries;
 
int ft[1101][1101];
void reset() {
    memset(ft, 0, sizeof(ft));
}
int qry(int x, int y) {
    int s = 0;
    while (y) {
        s += ft[x][y];
        y -= y&-y;
    }
    return s;
}
void upd(int x, int y, int v) {
    while (y <= m) {
        ft[x][y] += v;
        y += y&-y;
    }
}
 
// find number of ones in the rectangle defined by query i
int qryQuery(int i) {
    query q = queries[i];
    int s = 0;
    for (int i = q.x; i <= q.a; i++) {
        s += qry(i, q.b) - qry(i, q.y-1);
    }
    return s;
}
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    freopen("engineer.in", "r", stdin);
    freopen("engineer.out", "w", stdout);
 
    ri(n, m);
    vector<pair<int, ii>> things;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ri(A[i][j]);
            things.pb(mp(A[i][j], mp(i, j)));
        }
    }
    sort(things.begin(), things.end());
 
    ri(q);
    for (int i = 0; i < q; i++) {
        int x, y, a, b, k; ri(x, y, a, b, k);
        queries.pb(query{x,y,a,b,k});
        L[i] = 0, R[i] = things.size();
    }
 
	vector<int> check[things.size()];
    while (true) {
        bool done = true;
        reset();
        for (int i = 0; i < q; i++) {
            if (L[i] != R[i]) {
                done = false;
                check[(L[i]+R[i])/2].pb(i);
            }
        }
        if (done) break;
 
        for (int i = 0; i < things.size(); i++) {
            auto thing = things[i].s;
            upd(thing.f+1, thing.s+1, 1);
            if (check[i].empty()) continue;
 
            for (int qryIdx : check[i]) {
                int num = qryQuery(qryIdx);
                //cout << num << " " << qryIdx << " " << i << endl;
                if (num >= queries[qryIdx].k) {
                    R[qryIdx] = i;
                } else {
                    L[qryIdx] = i+1;
                }
            }
            check[i].clear();
        }
    }
 
    for (int i = 0; i < q; i++) {
        cout << things[L[i]].f << "\n";
    }
 
    return 0;
}
