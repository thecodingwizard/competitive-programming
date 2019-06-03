#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <string>
#define INF 1000000000

using namespace std;

int N, m, n;
char type;

int main() {
    cin >> N;
    while (N-- > 0) {
        cin >> type >> m >> n;
        if (type == 'r' || type == 'Q') {
            // rook or queen
            cout << min(m, n) << endl;
        } else if (type == 'k') {
            // knight
            cout << ((m + 1)/2) * ((n + 1)/2) + (m/2) * (n/2) << endl;
        } else if (type == 'K') {
            // king
            cout << ((m + 1)/2) * ((n + 1)/2) << endl;
        }
    }
    return 0;
}