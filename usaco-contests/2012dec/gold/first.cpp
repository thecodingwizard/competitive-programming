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
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

#define INF 1000000000
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

struct node {
    node *children[26];
    bool endPoint;
    node() {
        for (int i = 0; i < 26; i++) children[i] = nullptr;
        endPoint = false;
    }
    void insert(const string &s, int idx) {
        if (idx == s.length()) {
            endPoint = true;
            return;
        }
        char c = s[idx] - 'a';
        if (children[c] == nullptr) children[c] = new node();
        children[c]->insert(s, idx+1);
    }
};

bool adjMatrix[26][26];
bool visited[26];
bool inStack[26];

bool isValid(int node) {
    visited[node] = true;
    inStack[node] = true;
    for (int i = 0; i < 26; i++) {
        if (!adjMatrix[node][i]) continue;
        if (!visited[i] && !isValid(i)) return false;
        if (visited[i] && inStack[i]) return false;
    }
    inStack[node] = false;
    return true;
}

int main() {
    freopen("first.in", "r", stdin);
    freopen("first.out", "w", stdout);

    int n;
    cin >> n;
    string strings[n]; for (int i = 0; i < n; i++) cin >> strings[i];
    node trie;
    for (int i = 0; i < n; i++) trie.insert(strings[i], 0);
    vector<string> valid;
    for (int i = 0; i < n; i++) {
        memset(adjMatrix, false, sizeof adjMatrix);
        node *curNode = &trie;
        int wordIdx = 0;
        while (wordIdx < strings[i].length()) {
            int charIdx = strings[i][wordIdx++] - 'a';
            if (curNode->endPoint) goto endPoint;
            for (int j = 0; j < 26; j++) {
                if (j == charIdx) {
                    continue;
                }
                if (curNode->children[j] != nullptr) {
                    adjMatrix[charIdx][j] = true;
                }
            }
            curNode = curNode->children[charIdx];
        }
        memset(visited, false, sizeof visited);
        memset(inStack, false, sizeof inStack);
        for (int j = 0; j < 26; j++) if (!visited[j] && !isValid(j)) goto endPoint;
        valid.push_back(strings[i]);
        endPoint:
        continue;
    }

    cout << valid.size() << endl;
    for (string s : valid) cout << s << endl;

    return 0;
}
