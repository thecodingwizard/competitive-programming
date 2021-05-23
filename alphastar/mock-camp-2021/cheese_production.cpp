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

const long double inf = 1e18;

struct machine {
    ll d, p, r, m;
};
vector<machine> machines;
bool operator <(const machine &a, const machine &b) {
    return a.d < b.d;
}

struct line {
    ll slope, intercept;
    mutable long double point; // point at which line becomes irrelevant
    bool isQuery;
    bool operator<(const line &b) const {
        if (b.isQuery) return point < b.point;
        return slope < b.slope;
    }
};
multiset<line, less<line>> lines;
long double intercept(line a, line b) {
    return ((long double)(b.intercept-a.intercept))/(a.slope-b.slope);
}
// if this function returns true, b is irrelevant
bool checkIntersect(multiset<line>::iterator a, multiset<line>::iterator b) {
    if (b == lines.end()) {
        a->point = inf;
        return false;
    }
    if (a->slope == b->slope) {
        a->point = a->intercept > b->intercept ? inf : -inf;
    } else {
        a->point = intercept(*a, *b);
    }
    return a->point >= b->point;
}

void addLine(line add) {
    multiset<line>::iterator it = lines.insert(add);
    multiset<line>::iterator after = it; after++;
    auto before = it;
    while (checkIntersect(it, after)) after = lines.erase(after);
    if (before != lines.begin() && checkIntersect(--before, it)) checkIntersect(before, it = lines.erase(it));
    while ((it = before) != lines.begin() && (--before)->point >= it->point) {
        checkIntersect(before, lines.erase(it));
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, c, k; cin >> n >> c >> k;
    F0R(i, n) {
        int d, p, r, m; cin >> d >> p >> r >> m;
        machines.pb(machine{d,p,r,m});
    }

    sort(all(machines));

    addLine({0, c, 0, false});
    for (auto curMachine : machines) {
        ll day = curMachine.d;
        auto l = *lines.lower_bound(line{0,0,(long double)day,1});
        ll money = l.slope*day+l.intercept;
        //cout << "on day " << day << ", using machine " << lines[0].m.d << endl;
        if (money >= curMachine.p) {
            ll dpVal = money - curMachine.p;
            line add = {curMachine.m, -(ll)curMachine.d*curMachine.m-curMachine.m + curMachine.r+dpVal, 0, false};
            addLine(add);
        } else {
            continue;
        }
    }

    ll day = k+1;
    //cout << "on day " << day << ", using machine " << lines[0].m.d << endl;
    auto l = *lines.lower_bound(line{0,0,(long double)day,1});
    ll money = l.slope*day+l.intercept;
    /*
    if (lines[0].m.d != -1) {
        money = max(money, money - lines[0].m.r + lines[0].m.m);
    }
    */
    cout << money << endl;

    return 0;
}
