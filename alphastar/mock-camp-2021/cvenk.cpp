#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

struct node {
    ll numTourists = 0;
    ll size = 0;
    ll downDist = -1, rightDist = -1;
    ll cost = 0;
    node *down = nullptr, *right = nullptr;
};

node *root = new node();

void genGraph(node *root, vector<string> &people, int index, int dir) {
    if (dir == 0) {
        // going down
        map<int, vector<string>> goingDown;
        map<int, int> downIndex;
        for (auto &person : people) {
            int downDist = 0;
            bool isGoingRight = false;
            int i;
            int lastI = -1;
            for (i = index; i >= 0; i--) {
                if (person[i] == 'D') {
                    downDist += (1 << i);
                    lastI = i;
                } else if (person[i] == 'R') {
                    isGoingRight = true;
                    break;
                }
            }
            if (downDist == 0 && !isGoingRight) {
                // tourist stopped
                root->numTourists++;
            } else if (downDist > 0) {
                // cout << person << " is going down " << downDist << endl;
                goingDown[downDist].push_back(person);
                downIndex[downDist] = lastI-1;
            }
        }
        node *curNode = root;
        int prevDist = 0;
        for (auto &x : goingDown) {
            curNode->downDist = x.f - prevDist;
            curNode->down = new node();
            genGraph(curNode->down, x.s, downIndex[x.f], 1);
            curNode = curNode->down;
            prevDist = x.f;
        }
    } else {
        // cout << "Going right..." << endl;
        // going right
        map<int, vector<string>> goingRight;
        map<int, int> rightIndex;
        for (auto &person : people) {
            int rightDist = 0;
            bool isGoingDown = false;
            int i;
            int lastI = -1;
            for (i = index; i >= 0; i--) {
                if (person[i] == 'R') {
                    rightDist += (1 << i);
                    lastI = i;
                } else if (person[i] == 'D') {
                    isGoingDown = true;
                    break;
                }
            }
            if (rightDist == 0 && !isGoingDown) {
                // tourist stopped
                root->numTourists++;
            } else if (rightDist > 0) {
                // cout << person << " is going right " << rightDist << endl;
                goingRight[rightDist].push_back(person);
                rightIndex[rightDist] = lastI-1;
            }
        }
        node *curNode = root;
        int prevDist = 0;
        for (auto &x : goingRight) {
            curNode->rightDist = x.f - prevDist;
            curNode->right = new node();
            genGraph(curNode->right, x.s, rightIndex[x.f], 0);
            curNode = curNode->right;
            prevDist = x.f;
        }
    }
}

void dfsInit(node *n) {
    // if (n->numTourists > 0) {
        // cout << "I found " << n->numTourists << " people!" << endl;
    // }
    // cout << n->size << endl;
    n->size = n->numTourists;
    if (n->downDist != -1) {
        // cout << "Going down " << n->downDist << endl;
        dfsInit(n->down);
        n->size += n->down->size;
        n->cost += (ll)n->downDist*n->down->size;
        n->cost += n->down->cost;
        // cout << "Going back up " << n->downDist << endl;
    }
    if (n->rightDist != -1) {
        // cout << "Going right " << n->rightDist << endl;
        dfsInit(n->right);
        n->size += n->right->size;
        n->cost += (ll)n->rightDist*n->right->size;
        n->cost += n->right->cost;
        // cout << "Going back left " << n->rightDist << endl;
    }
    // cout << "size: " << n->size << endl;
}

ll dfsBest(node *n) {
    ll best = 0;
    if (n->downDist != -1) {
        best = max(best, -(ll)(root->size)*n->downDist+(ll)2*(n->down->size)*n->downDist + dfsBest(n->down));
    }
    if (n->rightDist != -1) {
        best = max(best, -(ll)(root->size)*n->rightDist+(ll)2*(n->right->size)*n->rightDist + dfsBest(n->right));
    }
    return best;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<string> tourists;
    ll totCost = 0;
    F0R(i, n) {
        int r, s; cin >> r >> s;
        totCost += r + s;

        node *cur = root;
        string person = "";
        for (int x = 30; x >= 0; x--) {
            if (r >= (1 << x)) {
                person = "D" + person;
                r -= (1 << x);
            } else if (s >= (1 << x)) {
                person = "R" + person;
                s -= (1 << x);
            } else {
                person = "S" + person;
            }
        }
        // cout << person << endl;
        tourists.pb(person);
    }

    genGraph(root, tourists, 30, 0);
    genGraph(root, tourists, 30, 1);

    root->numTourists /= 2;

    dfsInit(root);

    cout << totCost - dfsBest(root) << endl;

    return 0;
}
