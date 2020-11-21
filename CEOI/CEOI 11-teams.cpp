/*
 * Sort the people by increasing minimum team size.
 *
 * Start by forming one team that includes the person with the biggest size requirement; make this team exactly that size.
 * Then, greedily create as many teams as possible by taking people until there is enough people to satisfy the current selection; make this selection into a team and repeat.
 * For the leftover people, temporarily assign them all to the largest team.
 * Move the largest team to be at the end of the list of teams.
 *
 * Define breakpoint[i] = the index of the last person included in team i.
 * We want to greedily make breakpoint[i] as large as possible for each i; this allows us to reduce the size of the last team.
 *
 * But this doesn't always give us the optimal answer; we may minimize the size of the last team, but previous teams may now be bigger than the last team.
 * Let's make a list of team sizes. We're free to move people from team i to team i+1; we want to minimize the maximum team size.
 *
 * We can do this greedily: given a range of teams, we can sum up their sizes and evenly distribute the team members. However, we need to be sure that we don't end up
 * moving a team member from team i to team i-1, which is not allowed. So, starting from index 0, we keep increasing the size of the range until evenly distributing
 * the team members would violate the rule. After we find one range, we evenly distribute the team members, then we find another range, and so on.
 *
 * See implementation for more details
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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n; cin >> n;
    vector<ii> A;
    F0R(i, n) {
        int x; cin >> x; A.pb(mp(x,i+1));
    }
    sort(all(A));

    int teams = 1;
    vector<int> breakpoints;
    for (int i = 0; i < n-A.back().f; i++) {
        int curSz = 1;
        while (curSz < A[i].f && i+1 < n-A.back().f) {
            curSz++;
            i++;
        }
        if (curSz >= A[i].f) {
            teams++;
            breakpoints.pb(i);
        }
    }

    breakpoints.pb(n-1);

    for (int i = breakpoints.size()-2; ~i; i--) {
        int j;
        for (j = breakpoints[i+1]-A[breakpoints[i+1]].f; ; j--) {
            if (j-(i==0?-1:breakpoints[i-1]) >= A[j].f) break;
        }
        breakpoints[i] = j;
    }

    for (int i = 0; i < (int)breakpoints.size()-1; i++) {
        int curSize = breakpoints[i]-(i==0?-1:breakpoints[i-1]);
        int j;
        for (j = i+1; j < (int)breakpoints.size(); j++) {
            int nxtSize = breakpoints[j]-breakpoints[j-1];
            if (nxtSize < (curSize+nxtSize)/(j-i+1)) {
                curSize += nxtSize;
            } else {
                break;
            }
        }
        for (int k = i; k < j; k++) {
            breakpoints[k] = (k==0?-1:breakpoints[k-1]) + curSize/(j-i);
            if (curSize % (j-i) >= j-k) {
                breakpoints[k]++;
            }
        }
        i = j-1;
    }

    cout << teams << endl;
    int curIdx = 0;
    for (int x : breakpoints) {
        cout << x - curIdx + 1;
        assert(x-curIdx+1>=A[x].f);
        for (; curIdx <= x; curIdx++) cout << " " << A[curIdx].s;
        cout << endl;
    }

    return 0;
}
