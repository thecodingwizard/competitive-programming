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

using namespace std;

#define INF 1000000000
typedef vector<int> vi;

map<string, int> r, setSize;
map<string, string> p;

string findSet(const string &i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
bool isSameSet(const string &i, const string &j) { return findSet(i) == findSet(j); }
void unionSet(const string &i, const string &j) {
    if (!isSameSet(i, j)) {
        string x = findSet(i), y = findSet(j);
        // rank is used to keep the tree short
        if (r[x] > r[y]) { p[y] = x; setSize[x] += setSize[y]; }
        else                   { p[x] = y; setSize[y] += setSize[x];
            if (r[x] == r[y]) r[y]++; } } }
int sizeOfSet(const string &i) { return setSize[findSet(i)]; }

int main() {
    int N;
    cin >> N;
    while (N--) {
        r.clear();
        setSize.clear();
        p.clear();
        int F;
        cin >> F;
        string a, b;

        while (F--) {
            cin >> a >> b;
            if (p.find(a) == p.end()) {
                p[a] = a;
                r[a] = 0;
                setSize[a] = 1;
            }
            if (p.find(b) == p.end()) {
                p[b] = b;
                r[b] = 0;
                setSize[b] = 1;
            }
            unionSet(a, b);
            cout << sizeOfSet(a) << endl;
        }
    }
    return 0;
}