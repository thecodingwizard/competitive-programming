#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<char> letter;
    vector<int> prevIdx;
    vector<int> len;
    vector<int> curIdx;

    int n; cin >> n;
    int jmp[n][20];
    F0R(i, n) {
        char c; cin >> c;
        if (c == 'T') {
            char a; cin >> a;
            letter.pb(a);
            prevIdx.pb(prevIdx.size()-1);
            if (prevIdx[i] == -1) len.pb(0);
            else len.pb(len[prevIdx[i]]+1);
            jmp[i][0] = (i == 0 ? 0 : curIdx[i-1]);
            curIdx.pb(i);
        } else if (c == 'P') {
            int x; cin >> x;
            int cur = i-1;
            for (int j = 19; ~j; j--) {
                if (len[jmp[cur][j]] >= x) {
                    cur = jmp[cur][j];
                }
            }
            cout << letter[cur] << endl;
            i--; n--;
            continue;
        } else {
            int x; cin >> x;
            int nxt = prevIdx[i-x];
            prevIdx.pb(i-1);
            letter.pb(letter[nxt]);
            len.pb(len[nxt]);
            jmp[i][0] = jmp[nxt][0];
            curIdx.pb(nxt);
        }
        FOR(j, 1, 20) {
            jmp[i][j] = jmp[jmp[i][j-1]][j-1];
        }
    }

    return 0;
}
