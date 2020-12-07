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
 
int dx[4]{-1,0,1,0};
int dy[4]{0,-1,0,1};
int main() {
    cin.tie(0)->sync_with_stdio(0);
 
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        char A[n][n]; F0R(i, n) F0R(j, n) cin >> A[i][j];
 
        int num[n][n];
        F0R(i, n) F0R(j, n) num[i][j] = -1;
 
        F0R(i, n) {
            F0R(j, n) {
                if (A[i][j] == 'X') num[i][j] = (i+j)%3;
            }
        }
 
        int ct[3]{0};
        F0R(i, n) {
            F0R(j, n) {
                if (num[i][j] >= 0) ct[num[i][j]]++;
            }
        }
 
        int magic = 0;
        FOR(i, 1, 3) if (ct[i] < ct[magic]) magic = i;
 
        F0R(i, n) {
            F0R(j, n) {
                cout << (num[i][j] == magic ? 'O' : A[i][j]);
            }
            cout << "\n";
        }
    }
 
    return 0;
}
