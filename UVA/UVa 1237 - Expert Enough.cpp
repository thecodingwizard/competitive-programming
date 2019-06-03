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

using namespace std;

#define INF 1000000000
typedef vector<int> vi;

struct Vendor {
    string name;
    int low{};
    int high{};
};

int main() {
    int T;
    cin >> T;
    while (T--) {
        int D, l, h;
        string n;
        cin >> D;
        Vendor vendors[D];
        for (int i = 0; i < D; i++) {
            cin >> n >> l >> h;
            vendors[i].name = n;
            vendors[i].low = l;
            vendors[i].high = h;
        }
        int Q, p;
        cin >> Q;
        Vendor ans = Vendor();
        while (Q--) {
            cin >> p;
            bool bad = false;
            for (auto &vendor : vendors) {
                if (vendor.low <= p && vendor.high >= p) {
                    if (!ans.name.empty()) {
                        cout << "UNDETERMINED" << endl;
                        bad = true;
                        break;
                    } else {
                        ans = vendor;
                    }
                }
            }
            if (ans.name.empty() && !bad) {
                cout << "UNDETERMINED" << endl;
            } else if (!bad) {
                cout << ans.name << endl;
            }
            ans.name = "";
        }
        if (T) cout << endl;
    }
    return 0;
}