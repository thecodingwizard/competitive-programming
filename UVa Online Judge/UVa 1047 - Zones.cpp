#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#define LSOne(S) (S & (-S))

using namespace std;

#define INF 1000000000
typedef vector<int> vi;

struct Overlap {
    int zones = 0;
    int val = 0;
};

int count(int a)
{
    int c = 0;
    while(a!=0)
    {
        c++;
        a-=LSOne(a);
    }
    return c;
}

int main() {
    int n, N, c = 1;
    while (cin >> n >> N && (n || N)) {
        int towers[n];
        for (int i = 0; i < n; i++) {
            cin >> towers[i];
        }
        int m;
        cin >> m;
        Overlap overlaps[m];
        for (int i = 0; i < m; i++) {
            int ct;
            cin >> ct;
            int zone;
            for (int j = 0; j < ct; j++) {
                cin >> zone;
                overlaps[i].zones |= 1 << zone-1;
            }
            cin >> overlaps[i].val;
        }

        int ans = 0;
        int selected = 0;
        for(int k=1;k<(1<<(n));k++) {
            if (count(k) == N) {
                int sum = 0;
                for (int i = 0; i < n; i++) {
                    int j = 1 << i;
                    if (k & j) {
                        // tower i is in subset
                        sum += towers[i];
                    }
                }
                for (auto &overlap : overlaps) {
                    int ct = count(k & overlap.zones);
                    if (ct > 1) {
                        sum -= (overlap.val)*(ct-1);
                    }
                }
                if (ans < sum) {
                    ans = sum;
                    selected = k;
                }
            }
        }

        cout << "Case Number  " << c++ << endl;
        cout << "Number of Customers: " << ans << endl;
        cout << "Locations recommended:";
        for (int i = 0; i < n; i++) {
            int j = 1 << i;
            if (selected & j) {
                cout << " " << i + 1;
            }
        }
        cout << endl << endl;
    }
    return 0;
}