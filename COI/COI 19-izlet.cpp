/*
 * https://codeforces.com/blog/entry/66506
 *
 * Define f(u, v) = # of distinct colors in path from u to v
 *
 * Compress all sets of nodes where f(u, v) = 1 for any pair of nodes (u, v) in the set.
 * 
 * Next, find all the 2-components, where a 2-component denotes a maximal set of nodes
 * where f(u, v) = 2 for all pairs of nodes (u, v) in the set.
 *
 * Note that each 2-component forms a contiguous section in the final tree.
 *
 * Also, a pair of 2-components will intersect in either 0 or 1 nodes.
 *
 * Finally, the 2-components will form "chains" that cover the whole tree.
 *
 * So, after we find all the 2-components, we can arbitrarily pick a starting -2component.
 * We pick a node inside that component and assign it a random color; call this node the "root" node.
 * Then, every other node in the component we can color a different color, and attach the
 * node to the root node.
 *
 * Next, we pick another 2-component connected to a 2-component that has already been processed.
 * In this component that we pick, note that exactly one node will have a color assigned to
 * it already. To find the color of the remaining nodes, run a dfs from one of the remaining
 * nodes, keeping track of the # of unique colors in our DFS path. If we encounter a node
 * where the # of unique colors in the DFS path equals f(sourceNode, currentNode)
 * then we know that the color of the source node & the remaining nodes of the 2-component
 * is the same as the color of the current node we're on. If, after the DFS, we don't find
 * such a node, then the color of the remaining nodes of the component should be a new color.
 *
 * Repeat for the remaining 2-components. Then "uncompress" the 1-components.
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

#define maxn 3000
int n; 
int input[maxn][maxn];

vector<int> nodes; // stores nodes remaining after 1's are compressed
map<int, vector<int>> nodesInOneComponent;
void compressOnes() {
    vector<bool> done(n, 0);
    F0R(i, n) {
        if (done[i]) continue;
        nodes.pb(i);
        done[i] = true;
        F0R(j, n) {
            if (input[i][j] == 1 && j != i) {
                nodesInOneComponent[i].pb(j);
                done[j] = true;
            }
        }
    }
}

vector<vector<int>> twoComponents;
bool inSameComponent[maxn][maxn];
vector<int> components[maxn];
void findTwos() {
    for (int n1 : nodes) {
        for (int n2 : nodes) {
            if (inSameComponent[n1][n2]) continue;
            if (input[n1][n2] != 2) continue;

            twoComponents.pb(vector<int>());
            twoComponents.back().pb(n1);
            twoComponents.back().pb(n2);
            for (int n3 : nodes) {
                if (input[n1][n3] == 2 && input[n2][n3] == 2) {
                    twoComponents.back().pb(n3);
                }
            }

            for (int x : twoComponents.back()) {
                for (int y : twoComponents.back()) {
                    inSameComponent[x][y] = 1;
                }
                components[x].pb(twoComponents.size()-1);
            }
        }
    }

    /*
    for (auto x : twoComponents) {
        for (auto y : x) {
            cout << y << " ";
        }
        cout << endl;
    }
    cout << "---" << endl;
    */
}

int assignedColor[maxn];
vector<ii> outputEdges;
vector<int> adj[maxn];
bool inQueue[maxn];

map<int, int> colors;
int target = -1;
int findColor(int u, int p) {
    if ((int)colors.size() == input[target][u]) {
        return assignedColor[u];
    }
    for (int v : adj[u]) {
        if (v == p) continue;
        colors[assignedColor[v]]++;

        int r = findColor(v, u);

        colors[assignedColor[v]]--;
        if (colors[assignedColor[v]] == 0) {
            colors.erase(assignedColor[v]);
        }
        if (r != 0) return r;
    }
    return 0;
}

void buildTree() {
    int colors = 2;
    assignedColor[nodes[0]] = 1;
    queue<int> q;
    for (int c : components[nodes[0]]) {
        q.push(c);
        inQueue[c] = true;
    }

    while (!q.empty()) {
        int c = q.front(); q.pop();
        int rootNode = -1;
        int childNode = -1;
        for (int x : twoComponents[c]) {
            if (assignedColor[x] > 0) {
                assert(rootNode == -1);
                rootNode = x;
            } else {
                childNode = x;
            }
        }

        adj[childNode].pb(rootNode);
        adj[rootNode].pb(childNode);
        outputEdges.pb(mp(childNode, rootNode));

        target = childNode;
        assignedColor[childNode] = findColor(childNode, childNode);
        if (assignedColor[childNode] == 0) {
            assignedColor[childNode] = colors++;
        }

        for (int x : twoComponents[c]) {
            if (x != rootNode && x != childNode) {
                assignedColor[x] = assignedColor[childNode];
                adj[x].pb(rootNode);
                adj[rootNode].pb(x);
                outputEdges.pb(mp(x, rootNode));
            }
            for (int c : components[x]) {
                if (!inQueue[c]) {
                    q.push(c);
                    inQueue[c] = true;
                }
            }
        }
    }
}

void decompressOnes() {
    for (int x : nodes) {
        for (int y : nodesInOneComponent[x]) {
            outputEdges.pb(mp(x, y));
            assignedColor[y] = assignedColor[x];
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int subtask; cin >> subtask;
    cin >> n;
    F0R(i, n) {
        F0R(j, n) {
            cin >> input[i][j];
        }
    }

    compressOnes();

    findTwos();

    buildTree();

    decompressOnes();

    F0R(i, n) cout << assignedColor[i] << " ";
    cout << endl;
    for (auto x : outputEdges) cout << x.f+1 << " " << x.s+1 << endl;
    assert((int)outputEdges.size()==n-1);
    F0R(i, n) assert(assignedColor[i]>0);

    return 0;
}
