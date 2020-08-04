/*
 * Make n+m nodes: one node for each of the rows and one node for each of the products.
 *
 * Draw directed edge from a row to a product if the row has an extra product (draw one edge per extra product).
 *
 * Draw directed edge from a product to a row if the row lacks that product.
 *
 * Find euler tour of the entire graph. For each euler tour, we need to take one
 * extra step to move a product into the empty space, then move it back.
 */

#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second

int n, m; 
int ct[400][400];
int nums[400][400];
vector<int> adj[800]; // 0-399 is rows, 400-799 is products

vector<int> eulerTour(int s) {
    vector<int> ans, idx(800, 0), st;
    st.push_back(s);
    while (!st.empty()) {
        int u = st.back();
        if (idx[u] < (int)adj[u].size()) {
            st.push_back(adj[u][idx[u]++]);
        } else {
            ans.push_back(u);
            st.pop_back();
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

vector<ii> commands;

int findInRow(int row, int tgt) {
    if (n*m == row) return -1;
    for (int i = 0; i < m; i++) {
        if (nums[row][i] == tgt) return i;
    }
    assert(false);
}

void move(int fromRow, int tgtNumber, int toRow) {
    //cout << "move " << fromRow << " " << tgtNumber << " " << toRow << endl;
    int idx = findInRow(fromRow, tgtNumber), tgtIdx = findInRow(toRow, -1);
    if (idx != -1) {
        nums[fromRow][idx] = -1;
    }
    if (tgtIdx != -1) {
        nums[toRow][tgtIdx] = tgtNumber;
    }
    int fr = idx == -1 ? n*m+1 : (fromRow*m+idx+1);
    int to = tgtIdx == -1 ? n*m+1 : (toRow*m+tgtIdx+1);
    commands.push_back(make_pair(fr, to));
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> nums[i][j]; nums[i][j]--;
            ct[i][nums[i][j]]++;
        }
        for (int j = 0; j < m; j++) {
            if (ct[i][j] > 1) {
                for (int k = 2; k <= ct[i][j]; k++) {
                    adj[i].push_back(400+j);
                }
            } else if (ct[i][j] == 0) {
                adj[400+j].push_back(i);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!adj[i].empty()) {
            vector<int> tour = eulerTour(i);

            /*
            for (int x : tour) {
                cout << x << " ";
            }
            cout << endl;
            */

            move(tour[0], tour[1]-400, n*m);
            for (int i = (int)tour.size()-1; i >= 2; i -= 2) {
                move(i-2 == 0 ? n*m : tour[i-2], tour[i-1]-400, tour[i]);
            }
            for (int x : tour) {
                vector<int>().swap(adj[x]);
            }
        }
    }
    cout << commands.size() << endl;
    for (ii x : commands) cout << x.f << " " << x.s << endl;

    return 0;
}
