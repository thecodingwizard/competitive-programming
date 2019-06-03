#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>

#define INF 1000000000

using namespace std;


int main() {
    int N, n, *machine = new int[1000001];
    map<int, int> lastOccurrence;
    cin >> N;
    while (N--) {
        cin >> n;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> machine[i];
        }
        int start = 0, end = 0;
        for (; end < n; end++) {
            if (lastOccurrence.find(machine[end]) != lastOccurrence.end()) {
                start = max(lastOccurrence[machine[end]] + 1, start);
            }
            lastOccurrence[machine[end]] = end;
            ans = max(ans, end - start + 1);
        }
        cout << ans << endl;
        lastOccurrence.clear();
    }
    return 0;
}