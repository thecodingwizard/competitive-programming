/*
 * First, move all coins into the closet spot in the rectangle
 *
 * Then, greedily go from left to right. Every time we encounter a cell
 * with some coins, we first fill up everything in that row from left to right,
 * then we fill up evertyhing in the row above it from left to right
 * (both only up to the column we're currently on). Any leftovers we move
 * it all one to the right.
 *
 * I think (??) this can be proved to be optimal
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    long long ans = 0;
    int top[n+2], bot[n+2];
    for (int i = 1; i <= n; i++) top[i] = bot[i] = 0;
    for (int i = 0; i < 2*n; i++) {
        int a, b; cin >> a >> b;
        if (a < 1) {
            ans += 1-a;
            a = 1;
        }
        if (a > n) {
            ans += a - n;
            a = n;
        }
        if (b < 1) {
            ans += 1 - b;
            b = 1;
        }
        if (b > 2) {
            ans += b - 2;
            b = 2;
        }
        if (b == 1) bot[a]++;
        else top[a]++;
    }
    int topIdx = 1, botIdx = 1;
    for (int i = 1; i <= n; i++) {
        while (topIdx <= i && top[i] > 0) {
            ans += i - topIdx;
            topIdx++;
            top[i]--;
        }
        while (botIdx <= i && bot[i] > 0) {
            ans += i - botIdx;
            botIdx++;
            bot[i]--;
        }
        while (botIdx <= i && top[i] > 0) {
            ans += i - botIdx + 1;
            botIdx++;
            top[i]--;
        }
        while (topIdx <= i && bot[i] > 0) {
            ans += i - topIdx + 1;
            topIdx++;
            bot[i]--;
        }
        top[i+1] += top[i];
        bot[i+1] += bot[i];
        ans += top[i] + bot[i];
    }
    cout << ans << endl;

    return 0;
}
