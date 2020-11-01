#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair

int main() {
    int n, t, p; cin >> n >> t >> p; --p;

    int weight[t]; for (int i = 0; i < t; i++) weight[i] = n;
    int A[n][t];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t; j++) {
            cin >> A[i][j];
            weight[j] -= A[i][j];
        }
    }
    vector<pair<int, ii>> people;
    for (int i = 0; i < n; i++) {
        int score = 0, tasks = 0;
        for (int j = 0; j < t; j++) {
            score += weight[j] * A[i][j];
            tasks += A[i][j];
        }
        people.push_back(mp(-score, mp(-tasks, i)));
    }
    sort(people.begin(), people.end());
    for (int i = 0; i < n; i++) {
        if (people[i].s.s == p) {
            cout << -people[i].f << " " << i+1 << endl;
        }
    }

    return 0;
}
