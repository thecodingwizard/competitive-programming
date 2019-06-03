#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <bitset>

#define INF 1000000000

using namespace std;

int main() {
    bitset<1000001> bset;

    int n, m, start, end, interval;
    while (cin >> n >> m && (n || m)) {
        bset.reset();

        bool bad = false;
        for (int i = 0; i < n; i++) {
            cin >> start >> end;
            if (bad) continue;
            for (size_t j = start; j < end; j++) {
                if (bset.test(j)) {
                    bad = true;
                    break;
                }

                bset.set(j);
            }
        }

        for (int j = 0; j < m; j++) {
            cin >> start >> end >> interval;
            if (bad) continue;
            for (; start < 1000001; start += interval) {
                for (size_t i = start; i < end; i++) {
                    if (i >= 1000001) goto end;
                    if (bset.test(i)) {
                        bad = true;
                        goto end;
                    }

                    bset.set(i);
                }
                end += interval;
            }
            end:
            continue;
        }

        if (bad) {
            cout << "CONFLICT" << endl;
        } else {
            cout << "NO CONFLICT" << endl;
        }
    }

    return 0;
}