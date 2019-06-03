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

#define INF 1000000000

using namespace std;

int main() {
    int N;
    cin >> N;
    cin.ignore();
    while (N--) {
        int e = 0, v = 0, count = 0;
        bitset<26> connected;
        char node1, node2;
        while(scanf("(%c,%c)\n", &node1, &node2)) {
            connected.set(static_cast<size_t>(node1 - 'A'));
            connected.set(static_cast<size_t>(node2 - 'A'));
            e++;
        }
        string nodes;
        getline(cin, nodes); // ignore next line filled with stars
        getline(cin, nodes);
        v = (nodes.length() + 1)/2;

        for (int i = 0; i < 26; i++) {
            if (connected[i]) count++;
        }
        int acorns = v - count;

        printf("There are %d tree(s) and %d acorn(s).\n", v - e - acorns, acorns);
    }
    return 0;
}