#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <map>

#define INF 1000000000

using namespace std;

int n;

int main() {
    cin >> n;
    while (n-- > 0) {
        int k, m, val;
        double cost = 0.0;
        char c;
        map<char, int> priceList;

        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> c >> val;
            priceList[c] = val;
        }

        cin >> m;
        cin.ignore();
        string s;
        for (int i = 0; i < m; i++) {
            getline(cin, s);
            for (char &c : s) {
                cost += priceList[c];
            }
        }

        printf("%0.2f$\n", cost/100.0);
    }
    return 0;
}