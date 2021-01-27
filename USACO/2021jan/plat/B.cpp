/*
 * Calculate at which row it's optimal to switch from column c1 to column c2
 *
 * You'll get a linear equation in r
 *
 * Find the lower hull of all the lines representing the columns; at each intersection
 * you should switch columns
 *
 * Iterate left to right through the columns; add the line representing the column
 * then answer all the queries for that column
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define F0R(i, n) for (int i = 0; i < n; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define ii pair<int, int>
#define pll pair<ll, ll>
#define f first
#define s second
#define pb push_back
#define mp make_pair

const int inf = 1000000010;
const ll llinf = 1000000000000000000;
const int maxn = 2e5+10;

ll n, m; 
ll C[maxn];
vector<ii> queries[maxn];
ll queryAns[maxn];

struct line {
    ll m, b;
    ll cost, startRow, endRow, startValue, col;
};

vector<line> lines;

pll getIntersection(line l1, line l2) {
    return mp(l2.b-l1.b, l1.m-l2.m);
}


ll getValueAt(line l, ll row) {
    //assert(row >= 1);
    return l.startValue + l.cost*(row-l.startRow);
}

ll intToX(pll intersection) {
    if (intersection.s < 0) {
        intersection.f *= -1;
        intersection.s *= -1;
    }
    return intersection.f/intersection.s+(intersection.f%intersection.s>0);
}

void addCol(int col) {
    //cerr << "Adding line for col " << col << endl;
    line colLine{-2*col, C[col]-col, C[col], -1, -1, -1, col};

    while (lines.size() >= 2) {
        line l1 = lines.back(); line l2 = lines[lines.size()-2];
        pll int1 = getIntersection(l1, l2), int2 = getIntersection(colLine, l1);
        if (int1.f*int2.s > int1.s*int2.f) {
            lines.pop_back();
        } else {
            break;
        }
    }

    while (!lines.empty()) {
        pll intersection = getIntersection(lines.back(), colLine);
        ll startRow = intToX(intersection);
        if (startRow <= 1) lines.pop_back();
        else break;
    }

    ll startRow = 1;
    if (!lines.empty()) {
        pll intersection = getIntersection(lines.back(), colLine);
        startRow = intToX(intersection);
        assert(startRow > 1);

        lines.back().endRow = startRow - 1;
        //assert(lines.back().startRow <= lines.back().endRow);
    }

    colLine.startRow = startRow;
    colLine.endRow = llinf;

    ll prevValue = (startRow == 1 ? 0 : getValueAt(lines.back(), startRow));
    ll prevCol = (lines.empty() ? 1 : lines.back().col);
    ll costToSwitchCols = (col-prevCol)*(startRow)*(startRow);
    colLine.startValue = prevValue + costToSwitchCols;

    lines.push_back(colLine);
}

void answerQueries(ll col) {
    int lineIdx = 0;
    //cerr << "Answering query for col " << col << endl;
    for (auto l : lines) {
        //cerr << l.startRow << " -- " << l.endRow << " -- " << l.col << " -- " << l.startValue << endl;
    }
    sort(all(queries[col]));
    for (auto qry : queries[col]) {
        ll row = qry.f;

        while (lines[lineIdx].endRow < row) lineIdx++;

        ll ans = getValueAt(lines[lineIdx], row);
        ans += (col - lines[lineIdx].col)*row*row;

        queryAns[qry.s] = ans;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> C[i];

    int q; cin >> q;
    F0R(i, q) {
        int x, y; cin >> x >> y;
        queries[y].pb(mp(x, i));
    }

    for (int col = 1; col <= m; col++) {
        addCol(col);
        answerQueries(col);
    }

    F0R(i, q) cout << queryAns[i] << "\n";

    return 0;
}
