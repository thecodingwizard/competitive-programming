/*
 * Solve using a sparse lazy seg tree
 * each node stores its maximum delta and its total delta
 * lazy: keep track of the increment and propagate increment to children
 */

#include <bits/stdc++.h>

using namespace std;

int n; 

struct node {
    int i, j;
    int mx = 0, delta = 0;
    node *left = nullptr, *right = nullptr;
    bool lazy = false;

    void init(int _inc) {
        delta = _inc*(j-i+1);
        mx = max(delta, 0);
    }

    void set(int _inc) {
        lazy = true;
        init(_inc);
    }

    void down() {
        if (lazy) {
            lazy = false;
            if (left != nullptr) left->set(delta/(j-i+1));
            if (right != nullptr) right->set(delta/(j-i+1));
        }
    }

    node *getLeft() {
        assert(i != j);
        if (left == nullptr) {
            left = new node;
            left->i = i; left->j = (i+j)/2;
            left->init(delta/(j-i+1));
        }
        return left;
    }

    node *getRight() {
        assert(i != j);
        if (right == nullptr) {
            right = new node;
            right->i = (i+j)/2+1; right->j = j;
            right->init(delta/(j-i+1));
        }
        return right;
    }
} st;

void upd(node *x, int l, int r, int d) {
    x->down();
    if (l <= x->i && r >= x->j) {
        x->set(d);
        //cout << x->i << "," << x->j << " mx is " << x->mx << ", delta = " << x->delta << endl;
        return;
    }
    if (l > x->j || r < x->i) return;
    upd(x->getLeft(), l, r, d);
    upd(x->getRight(), l, r, d);
    x->mx = max(x->getLeft()->mx, x->getLeft()->delta + x->getRight()->mx);
    x->delta = x->getLeft()->delta + x->getRight()->delta;
    //cout << x->i << "," << x->j << " mx is " << x->mx << ", delta = " << x->delta << endl;
}

int qry(node *x, int h) {
    x->down();
    if (x->mx <= h) {
        return x->j+1;
    } else if (x->i == x->j) {
        return x->i;
    }
    if (x->getLeft()->mx > h) {
        return qry(x->getLeft(), h);
    } else {
        return qry(x->getRight(), h-x->getLeft()->delta);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    cin >> n; st.i = 0; st.j = n-1;
    while (true) {
        char c; cin >> c;
        if (c == 'E') break;

        if (c == 'Q') {
            int h; cin >> h;
            cout << qry(&st, h) << "\n";
        } else {
            int a, b, d; cin >> a >> b >> d; --a; --b;
            upd(&st, a, b, d);
        }
    }

    return 0;
}
