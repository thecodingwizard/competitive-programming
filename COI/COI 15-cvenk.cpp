#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<ll, ll>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define inf 1000000010

int n; 
vector<ii> A;

int ctr = 1;
struct node {
    node *down = nullptr, *right = nullptr;
    ll numNodes = 0, distToParent = 0;
    int id = 0;
} root;

pair<char, int> getNextMove(ii x, int downDist, int rightDist) {
    char dir = 'S';
    int loc = 0;
    int i = 30;
    while (i >= 0) {
        char curDir = 'S';
        if (x.f & (1 << i)) curDir = 'D';
        if (x.s & (1 << i)) curDir = 'R';
        if (curDir != 'S') {
            if (downDist > 0 || rightDist > 0) {
                if (curDir == 'D') {
                    downDist -= (1 << i);
                } else {
                    rightDist -= (1 << i);
                }
                //cout << downDist << " "<< rightDist << " " << curDir << " " << i << endl;
                assert(downDist >= 0 && rightDist >= 0);
            } else {
                if (dir == 'S') dir = curDir;
                if (dir != curDir) break;
                loc += (1 << i);
            }
        }
        i--;
    }
    return mp(dir, loc);
}

void add(node *n, int downDist, int rightDist, vector<ii> A, bool isMovingDown) {
    vector<pair<int, ii>> movingDown, movingRight;

    for (auto x : A) {
        pair<char, int> c = getNextMove(x, downDist, rightDist);
        if (c.f == 'D') {
            movingDown.pb(make_pair(c.s+downDist, x));
        } else if (c.f == 'R') {
            movingRight.pb(make_pair(c.s+rightDist, x));
        }
    }
    sort(all(movingDown)); sort(all(movingRight));

    if (isMovingDown) {
        int prev = downDist;
        for (int i = 0; i < sz(movingDown); i++) {
            int iInitial = i;
            int nodeCt = 1;
            vector<ii> nextSet; nextSet.pb(movingDown[i].s);
            while (i+1 < sz(movingDown) && movingDown[i].f == movingDown[i+1].f) {
                i++;
                nodeCt++;
                nextSet.pb(movingDown[i].s);
            }
            n->down = new node;
            n->down->id = ctr++;
            n->down->distToParent = movingDown[i].f - prev;
            n->down->numNodes = sz(movingDown)-iInitial;
            add(n->down, movingDown[i].f, rightDist, nextSet, !isMovingDown);
            prev = movingDown[i].f;
            n = n->down;
        }
    } else {
        int prev = rightDist;
        for (int i = 0; i < sz(movingRight); i++) {
            int iInitial = i;
            int nodeCt = 1;
            vector<ii> nextSet; nextSet.pb(movingRight[i].s);
            while (i+1 < sz(movingRight) && movingRight[i].f == movingRight[i+1].f) {
                i++;
                nodeCt++;
                nextSet.pb(movingRight[i].s);
            }
            n->right = new node;
            n->right->id = ctr++;
            n->right->distToParent = movingRight[i].f - prev;
            n->right->numNodes = sz(movingRight)-iInitial;
            add(n->right, downDist, movingRight[i].f, nextSet, !isMovingDown);
            prev = movingRight[i].f;
            n = n->right;
        }
    }
}

ll solve(node *x, ll parentCt) {
    //cout << x->id << " has " << x->numNodes << " nodes and dist to parent of " << x->distToParent << endl;
    ll best = 0;
    if (x->down) {
        //cout << "moving down from " << x->id << endl;
        ll ex = x->numNodes - x->down->numNodes + parentCt;
        best = min(best, solve(x->down, ex) + x->down->distToParent*(ex) - x->down->numNodes*x->down->distToParent);
    } 
    if (x->right) {
        //cout << "moving right from " << x->id << endl;
        ll ex = x->numNodes - x->right->numNodes + parentCt;
        best = min(best, solve(x->right, ex) + x->right->distToParent*(ex) - x->right->numNodes*x->right->distToParent);
    } 
    return best;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    A.resize(n);
    F0R(i, n) cin >> A[i].f >> A[i].s;

    root.numNodes = n;
    add(&root, 0, 0, A, 0);
    add(&root, 0, 0, A, 1);

    ll base = 0;
    for (auto x : A) base += x.f + x.s;
    cout << solve(&root, 0) + base << endl;

    return 0;
}
