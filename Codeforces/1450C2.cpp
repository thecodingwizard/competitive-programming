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

        int numX[n][n], numY[n][n];
        F0R(i, n) F0R(j, n) numX[i][j] = numY[i][j] = -1;

        F0R(i, n) {
            F0R(j, n) {
                if (A[i][j] == 'X') numX[i][j] = (i+j)%3;
                if (A[i][j] == 'O') numY[i][j] = (i+j)%3;
            }
        }

        int ctX[3]{0}, ctY[3]{0};
        F0R(i, n) {
            F0R(j, n) {
                if (numX[i][j] >= 0) ctX[numX[i][j]]++;
                if (numY[i][j] >= 0) ctY[numY[i][j]]++;
            }
        }

        ii magic = mp(0, 1);
        F0R(i, 3) {
            F0R(j, 3) {
                if (i == j) continue;
                if (ctX[magic.f]+ctY[magic.s] > ctX[i]+ctY[j]) magic = mp(i, j);
            }
        }

        F0R(i, n) {
            F0R(j, n) {
                if (numX[i][j] == magic.f) cout << 'O';
                else if (numY[i][j] == magic.s) cout << 'X';
                else cout << A[i][j];
            }
            cout << "\n";
        }
    }

    return 0;
}
