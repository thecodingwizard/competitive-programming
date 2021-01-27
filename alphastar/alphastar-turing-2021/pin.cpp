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

int diffCt[50000][5];
int diffCt2[50000];
int diffCt3[50000];
unordered_map<string, int> maskCt;
unordered_map<string, int> maskCt2;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, d; cin >> n >> d;
    vector<string> A;
    unordered_map<string, int> all;
    F0R(i, n) {
        string s; cin >> s;
        A.pb(s);
        all[s] = i;
    }
    vector<char> chars;
    F0R(i, 26) chars.pb('a'+i);
    F0R(i, 10) chars.pb('0'+i);
    F0R(i, n) {
        F0R(j, 4) {
            for (auto c : chars) {
                if (c == A[i][j]) continue;
                string s2 = A[i]; s2[j] = c;
                if (all.count(s2)) {
                    diffCt[i][j]++;
                    diffCt[i][4]++;
                }
            }
        }
    }
    F0R(i, n) {
        F0R(j, 4) {
            FOR(k, j+1, 4) {
                string s2 = A[i];
                s2[j] = 'X'; s2[k] = 'X'; maskCt[s2]++;
                FOR(l, k+1, 4) {
                    s2 = A[i]; s2[j] = 'X'; s2[k] ='X'; s2[l] = 'X';
                    maskCt2[s2]++;
                }
            }
        }
    }
    F0R(i, n) {
        F0R(j, 4) {
            FOR(k, j+1, 4) {
                string s2 = A[i]; s2[j] = 'X'; s2[k] = 'X';
                diffCt2[i] += maskCt[s2] - 1 - diffCt[i][j] - diffCt[i][k];
                FOR(l, k+1, 4) {
                    s2 = A[i]; s2[j] = 'X'; s2[k] ='X'; s2[l] = 'X';
                    diffCt3[i] += maskCt2[s2] - 1 - diffCt[i][j] - diffCt[i][k] - diffCt[i][l];
                }
            }
        }
        diffCt3[i] -= 2*diffCt2[i];
    }

    ll sum = 0;
    F0R(i, n) {
        if (d == 1) {
            F0R(j, 4) sum += diffCt[i][j];
        } else if (d == 2) {
            sum += diffCt2[i];
        } else if (d == 3) sum += diffCt3[i];
        else {
            F0R(j, 4) sum -= diffCt[i][j];
            sum -= diffCt2[i];
            sum -= diffCt3[i];
            sum += n - 1;
        }
    }
    cout << sum/2 << endl;

    return 0;
}
