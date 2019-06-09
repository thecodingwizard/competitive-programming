/**
 * Subtask One: Brute force 2^n
 * Subtask Two: Nobody's friends with anyone else, sum all confidence values
 * Subtask Three: Everyone's friends with everyone else, take largest confidence value
 * Subtask Four: It's a tree, you can do dp[i][0] = max of subtree of i, cannot take i. dp[i][1] = max of subtree of i, can take i.
 * Subtask Five: It's a bipartite graph where each node has weight 1. You can do maximum independent set (N - MCBM)
 * Subtask Six: Use induction trick, processing protocols in reverse.
 * - Define host_val = host confidence
 *          my_val = my cofidence
 * - If protcol is IAmYourFriend:
 *      if host_val < my_val: ans += my_val; host_val = 0. We're gonna take my_val instead of host_val
 *      else: ans += my_val; host_val -= my_val; We're either gonna take host or take my val.
 * - If protocol is WeAreYourFriends:
 *      host_val = max(host_val, my_val). If we take the host, we can also choose to take me instead
 * - If protocol is MyFriendsAreYourFriends:
 *      host_val += my_val. If we're gonna take host, we might as well take me as well.
 * Credits to tmwilliamlin168 for explaining the solution to me :)
 */

#include <bits/stdc++.h>
#include "friend.h"

using namespace std;

#define FOR(a, b, c) for (int a = b; a < c; a++)
#define ll long long
#define vi vector<int>
#define pb push_back
#define mp make_pair

int memo[1000][2];
bool friends[1000][1000];
bool isLeft[1000];
bool visited[1000];
int *A;
int n;
void dfsVisited(int u, int p) {
    visited[u] = true;
    for (int v = 0; v < n; v++) {
        if (!friends[v][u]) continue;
        if (v == p || v == u) continue;
        dfsVisited(v, u);
    }
}
int run(int u, int canTake, int p) {
    if (memo[u][canTake] != -1) return memo[u][canTake];
    int ans = 0;
    // Option 1: Don't take u
    int opAns = 0;
    for (int v = 0; v < n; v++) {
        if (!friends[v][u]) continue;
        if (v == p || v == u) continue;
        opAns += run(v, 1, u);
    }
    ans = opAns;

    // Option 2: Take u
    if (canTake) {
        opAns = A[u];
        for (int v = 0; v < n; v++) {
            if (!friends[v][u]) continue;
            if (v == p || v == u) continue;
            opAns += run(v, 0, u);
        }
        ans = max(ans, opAns);
    }
    return memo[u][canTake] = ans;
}

int match[1000];
int aug(int u) {
    if (visited[u]) return 0;
    visited[u] = true;
    for (int v = 0; v < n; v++) {
        if (!friends[u][v] || u == v || isLeft[v]) continue;
        if (match[v] == -1 || aug(match[v])) {
            match[v] = u; return 1;
        }
    }
    return 0;
}

void dfsLeft(int u, int p, int l) {
    isLeft[u] = l;
    visited[u] = true;
    for (int v = 0; v < n; v++) {
        if (v == u || !friends[v][u] || visited[v]) continue;
        dfsLeft(v, u, !l);
    }
}

// Find out best sample
int findSample(int n2, int confidence[], int host[], int protocol[]) {
    n = n2;

    if (n <= 1000) {
        FOR(i, 0, n) FOR(j, 0, n) friends[i][j] = false;

        A = confidence;
        FOR(i, 1, n) {
            int h = host[i], p = protocol[i];
            if (p == 0) {
                // IAmYourFriend
                friends[i][h] = true;
                friends[h][i] = true;
            } else if (p == 1) {
                // MyFriendsAreYourFriends
                for (int u = 0; u < n; u++) {
                    if (!friends[u][h]) continue;
                    friends[u][i] = true;
                    friends[i][u] = true;
                }
            } else {
                // WeAreYourFriends
                friends[i][h] = true;
                friends[h][i] = true;
                for (int u = 0; u < n; u++) {
                    if (!friends[u][h] || u == h) continue;
                    friends[u][i] = true;
                    friends[i][u] = true;
                }
            }
        }
    }

    if (n <= 10) {
        // Subtask 1
        int ans = 0;
        for (int i = 0; i < (1 << n); i++) {
            int curAns = 0;
            bool invalid = false;
            for (int j = 0; j < n; j++) {
                if (!(i & (1 << j))) continue;
                for (int f = 0; f < n; f++) {
                    if (!friends[j][f] || j == f) continue;

                    if (i & (1 << f)) {
                        invalid = true;
                        break;
                    }
                }
                if (invalid) break;
                curAns += confidence[j];
            }
            if (!invalid) ans = max(ans, curAns);
        }
        return ans;
    } else {
        bool isSubtaskTwo = true;
        for (int i = 1; i < n; i++) {
            if (protocol[i] != 1) isSubtaskTwo = false;
        }
        if (isSubtaskTwo) {
            // Subtask two: Sum all confidence values
            int ans = 0;
            for (int i = 0; i < n; i++) ans += confidence[i];
            return ans;
        }

        bool isSubtaskThree = true;
        for (int i = 1; i < n; i++) {
            if (protocol[i] != 2) isSubtaskThree = false;
        }
        if (isSubtaskThree) {
            // Subtask Three: We Are Your Friends, entire graph is connected
            int ans = 0;
            for (int i = 0; i < n; i++) ans = max(ans, confidence[i]);
            return ans;
        }

        bool isSubtaskFour = true;
        for (int i = 1; i < n; i++) {
            if (protocol[i] != 0) isSubtaskFour = false;
        }
        if (isSubtaskFour) {
            // Subtask Four: Tree
            // Define dp[i][0] = max confidence of subtree of i, cannot take i
            //        dp[i][1] = max confidence of subtree of i, can take i
            for (int i = 0; i < n; i++) visited[i] = false;
            for (int i = 0; i < n; i++) memo[i][0] = memo[i][1] = -1;
            int ans = 0;
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    dfsVisited(i, i);
                    ans += run(i, 1, i);
                }
            }
            return ans;
        }

        bool isSubtaskFive = n <= 1000;
        for (int i = 1; i < n; i++) if (protocol[i] == 2 || confidence[i] != 1) isSubtaskFive = false;
        if (isSubtaskFive) {
            // Subtask Five: It's a bipartite graph, asking you to find maximum independent set
            for (int i = 0; i < n; i++) isLeft[i] = false;
            for (int i = 0; i < n; i++) visited[i] = false;
            for (int i = 0; i < n; i++) {
                if (!visited[i]) dfsLeft(i, i, 1);
            }
            int mcbm = 0;
            for (int i = 0; i < n; i++) match[i] = -1;
            for (int i = 0; i < n; i++) {
                if (!isLeft[i]) continue;
                for (int i = 0; i < n; i++) visited[i] = false;
                mcbm += aug(i);
            }
            return n - mcbm;
        }

        // Subtask Six: Induction Trick
        int ans = 0;
        for (int i = n - 1; i >= 1; i--) {
            int h = host[i];
            int h_val = confidence[h];
            int me_val = confidence[i];
            if (protocol[i] == 0) {
                if (me_val > h_val) {
                    confidence[h] = 0;
                    ans += me_val;
                } else {
                    confidence[h] -= me_val;
                    ans += me_val;
                }
            } else if (protocol[i] == 1) {
                confidence[h] += confidence[i];
            } else if (protocol[i] == 2) {
                confidence[h] = max(confidence[h], confidence[i]);
            }
            if (i == 1) ans += confidence[h];
        }
        return ans;
    }
}
