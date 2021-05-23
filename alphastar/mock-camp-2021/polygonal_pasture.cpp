/* 6/10 only :( */

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

long double eps = 0.6e-9;
int n;
vector<int> poly;
long double maxlen = -1;

long double getDegree(long double r, bool special) {
    long double tot = 0;

    for (long double x : poly) {
        long double angle = 2.0*asin(x/(2.0*r));
        if (x == maxlen && special) {
            special = false;
            tot -= angle;
        } else {
            tot += angle;
        }
    }
    
    return tot;
}

long double getArea(long double r, bool special) {
    long double tot = 0;

    for (long double x : poly) {
        long double angle = asin(x/(2.0*r));
        long double height = r*cos(angle);
        if (special && x == maxlen) {
            special = false;
            tot -= height*x/2.0;
        } else {
            tot += height*x/2.0;
        }
    }

    return tot;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    double sumlen = 0;
    if (n > 500) {
        //eps = 1e-10;
    }
    F0R(i, n) {
        int x; cin >> x;
        poly.pb(x);
        sumlen += x;
        maxlen = max(maxlen, (long double)x);
    }

    long double lo = maxlen/2, hi = sumlen/2, optimal = -1;
    while (lo < hi) {
        long double mid = (lo+hi)/2;
        long double totDegree = getDegree(mid, false);
        if (abs(totDegree - 2*M_PI) < eps) {
            optimal = mid;
            break;
        }
        if (totDegree < 2*M_PI) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    bool special = false;
    if (optimal == -1) {
        // special case >:-(
        // rip this does not work
        special = true;
        long double lo = 0, hi = M_PI;
        while (lo < hi) {
            long double mid = (lo+hi)/2;
            long double guess = maxlen/2/sin(mid/2);
            long double totDegree = getDegree(guess, true);
            //cout << guess << ": " << totDegree << endl;
            if (abs(totDegree) < eps) {
                optimal = guess;
                break;
            }
            if (totDegree < 0) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        assert(optimal != -1);
    }

    //cout << "Optimal radius: " << optimal << ". Special: " << special << endl;
    long double area = getArea(optimal, special);
    cout << fixed << setprecision(2);
    cout << area << endl;

    return 0;
}
