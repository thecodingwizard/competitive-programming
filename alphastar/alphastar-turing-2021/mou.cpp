// only 50% I think
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair
#define pb push_back

int delta[20001];

int main() {
    int n; cin >> n; assert(n <= 20000);
    for (int i = 0; i > -1; i++) {
        char c; cin >> c;
        if (c == 'Q') {
            int maxH; cin >> maxH;
            int curH = 0;
            int ans = -2;
            for (int j = 0; j <= n; j++) {
                curH += delta[j];
                if (curH > maxH) {
                    ans = j-1;
                    break;
                }
            }
            if (ans == -2) {
                cout << n << endl;
            } else {
                cout << ans << endl;
            }
        } else if (c == 'I') {
            int a, b, d; cin >> a >> b >> d;
            for (int j = a; j <= b; j++) {
                delta[j] = d;
            }
        } else {
            return 0;
        }
    }

    return 0;
}
