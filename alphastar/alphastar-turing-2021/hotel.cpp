#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define ii pair<int, int>
#define f first
#define s second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define pb push_back

int main() {
    int n, m, o; cin >> n >> m >> o;
    vector<ii> rooms, people;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b; rooms.pb(mp(a, b));
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; people.pb(mp(b, a));
    }
    sort(all(rooms)); sort(all(people));

    priority_queue<int> gains;
    priority_queue<ii> q;
    int idx = 0;
    ll ans = 0;
    for (auto room : rooms) {
        while (idx < m && people[idx].f <= room.s) {
            q.push(mp(people[idx].s, people[idx].f));
            idx++;
        }
        if (q.empty()) continue;
        int gain = q.top().f - room.f;
        if (gain <= 0) continue;
        if (o > 0) {
            q.pop();
            gains.push(-gain); --o;
            ans += gain;
        } else if (gain > -gains.top()) {
            ans += gains.top(); gains.pop();
            q.pop();
            gains.push(-gain);
            ans += gain;
        }
    }
    cout << ans << endl;

    return 0;
}
