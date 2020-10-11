/*
 * see: https://github.com/luciocf/Problems/blob/master/infoarena/unique.cpp
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
	void rs(string & x) { // read str
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
	void ws(string  s) { for (auto &c : s) wc(c); } // write str
	template<class T> void wi(T x, char after = '\0') { /// write int
		if (x < 0) wc('-'), x *= -1;
		int len = 0; for (;x>=10;x/=10) numBuf[len++] = '0'+(x%10);
		wc('0'+x); for (int i = len-1; i >= 0; i--) wc(numBuf[i]);
		if (after) wc(after);
	}
	void initO() { assert(atexit(flushOut) == 0); } /// auto-flush output
}

using namespace FastIO;

int A[100002];
int last[100002], ct[100002], sz[100002], pa[100002];

int get(int x) {
    return pa[x] == x ? x : pa[x] = get(pa[x]);
}

int ans = 1;
void unite(int a, int b) {
    a = get(a), b = get(b);
    if (a == b) return;
    if (sz[a] > sz[b]) swap(a, b);
    pa[a] = b;
    sz[b] += sz[a];
    ct[b] += ct[a];
}

int main() {
    freopen("unique.in", "r", stdin);
    freopen("unique.out", "w", stdout);

    int t; ri(t);
    while (t--) {
        int n; ri(n);
        for (int i = 0; i < n; i++) {
            ri(A[i]);
        }
        A[n] = n+1;

        for (int i = 0; i <= n+1; i++) {
            last[i] = -1;
            ct[i] = 0;
            pa[i] = i;
            sz[i] = 1;
        }

        ans = 1;
        stack<int> s;

        for (int i = 0; i <= n; i++) {
            // merge anything that's <= A[i]
            while (!s.empty() && A[s.top()] <= A[i]) {
                unite(s.top(), i);
                if (ct[get(s.top())] == A[s.top()]) {
                    ans = max(ans, sz[get(s.top())]-1);
                }
                s.pop();
            }

            // todo: update last for A[i]
            if (last[A[i]] != -1) {
                ct[get(last[A[i]])]--;
            }
            last[A[i]] = i;
            ct[get(i)]++;

            // todo: Add A[i] to stack
            s.push(i);
        }
        cout << ans << "\n";
    }

    return 0;
}
