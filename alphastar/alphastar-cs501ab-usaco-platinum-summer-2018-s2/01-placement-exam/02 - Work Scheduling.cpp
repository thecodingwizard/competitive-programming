/*
NOTE: Code does not pass all cases in time.

Work Scheduling
===============

Farmer John has so very many jobs to do! In order to run the farm
efficiently, he must make money on the jobs he does, each one of
which takes just one time unit.

His work day starts at time 0 and has 1,000,000,000 time units (!).  He
currently can choose from any of N (1 <= N <= 100,000) jobs
conveniently numbered 1..N for work to do. It is possible but
extremely unlikely that he has time for all N jobs since he can
only work on one job during any time unit and the deadlines tend
to fall so that he can not perform all the tasks.

Job i has deadline D_i (1 <= D_i <= 1,000,000,000). If he finishes
job i by then, he makes a profit of P_i (1 <= P_i <= 1,000,000,000).

What is the maximum total profit that FJ can earn from a given list
of jobs and deadlines?  The answer might not fit into a 32-bit
integer.

PROBLEM NAME: job

INPUT FORMAT:

* Line 1: A single integer: N

* Lines 2..N+1: Line i+1 contains two space-separated integers: D_i
        and P_i

SAMPLE INPUT:

3
2 10
1 5
1 7

OUTPUT FORMAT:

* Line 1: A single number on a line by itself that is the maximum
        possible profit FJ can earn.

SAMPLE OUTPUT:

17

OUTPUT DETAILS:

Complete job 3 (1,7) at time 1 and complete job 1 (2,10) at time 2
to maximize the earnings (7 + 10 -> 17).
*/

#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int n;
ii jobs[100001];
set<int> taken;

bool howToSort(ii a, ii b) {
    if (a.second == b.second) return a.first < b.first;
    return a.second > b.second;
}

int main() {
    cin >> n;
    vi times;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        jobs[i].first = a;
        jobs[i].second = b;
    }

    long long ans = 0;
    int maxIters = 0;

    sort(jobs, jobs + n, howToSort);

    for (int i = 0; i < n; i++) {
        int time = jobs[i].first;
        while (taken.find(time) != taken.end()) {
            time--;
            if (time <= 0) goto unfortunate;
        }
        taken.insert(time);
        ans += jobs[i].second;
        unfortunate:
        continue;
    }

    cout << ans << " " << maxIters;

    return 0;
}
