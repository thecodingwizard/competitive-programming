#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define ii pair<ll, ll>
#define f first
#define s second

struct vec {
    double x, y;
};
vec to_vec(ii a, ii b) {
    return vec{b.f-a.f,b.s-a.s};
}

double dot(vec a, vec b) { return (a.x*b.x+a.y*b.y); }
double norm_sq(vec v) { return v.x*v.x + v.y*v.y; }

double angle(ii a, ii o, ii b) {
    vec oa = to_vec(o, a), ob = to_vec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa)*norm_sq(ob)));
}

double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

bool ccw(ii p, ii q, ii r) {
    return cross(to_vec(p, q), to_vec(p, r)) > 0;
}

bool inPoly(ii p, vector<ii> A) {
    double sum = 0;
    A.push_back(A[0]);
    for (int i = 1; i < A.size(); i++) {
        ii prv = A[i-1], nxt = A[i];
        if (ccw(prv, p, nxt)) sum += angle(prv, p, nxt);
        else sum -= angle(prv, p, nxt);
    }
    return fabs(sum) + 0.00001 > M_PI ? 1 : 0;
}

int main() {
    int n, c; cin >> n >> c;

    map<ii, vector<ii>> adj;
    set<ii> points;

    // read in input, generate adj array
    for (int i = 0; i < n; i++) {
        ii a,b; cin >> a.f >> a.s >> b.f >> b.s;
        points.insert(a); points.insert(b);
        adj[b].push_back(a); adj[a].push_back(b);
    }

    // form polygons array
    vector<vector<ii>> polygons;
    set<ii> vis;
    for (ii p : points) {
        if (vis.count(p)) continue;
        ii x = p;
        vector<ii> poly;
        while (true) {
            vis.insert(x);
            poly.push_back(x);
            bool good = false;
            for (auto y : adj[x]) {
                if (vis.count(y)) continue;
                x = y;
                good = true;
                break;
            }
            if (!good) break;
        }
        polygons.push_back(poly);
    }

    /*
    for (auto x : polygons) {
        cout << "New Polygon" << endl;
        for (auto y : x) {
            cout << y.f << " " << y.s << endl;
        }
    }
    */

    // read in cows, generate strings
    vector<string> cows;
    for (int i = 0; i < c; i++) {
        ii cow; cin >> cow.f >> cow.s;
        string s = "";
        for (int j = 0; j < polygons.size(); j++) {
            if (inPoly(cow, polygons[j])) {
                s += "1";
            } else {
                s += "0";
            }
        }
        cows.push_back(s);
    }
    // sort strings, find answer
    int ans = 1;
    sort(cows.begin(), cows.end());
    int cur = 1;
    for (int i = 1; i < cows.size(); i++) {
        if (cows[i] == cows[i-1]) {
            cur++;
        } else {
            cur = 1;
        }
        ans = max(ans, cur);
    }
    cout << ans << endl;

    return 0;
}
