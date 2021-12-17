/*
https://www.quora.com/What-is-the-solution-of-the-IOI-2015-task-Towns
https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/IOI/IOI%2015-towns.cpp
*/

#include <bits/stdc++.h>
#include "towns.h"

using namespace std;

#define ii pair<int, int>
#define mp make_pair
#define inf 1e9;
#define f first
#define s second
#define pb push_back

map<ii, int> cached;
int getD(int a, int b) {
    if (a == b) return 0;
    if (a > b) swap(a, b);
    if (cached.count(mp(a, b))) return cached[mp(a, b)];
    return cached[mp(a, b)] = getDistance(a, b);
}

int hubDistance(int N, int sub) {
    cached.clear();

    int u, v;

    int maxDist = -1;
    for (int i = 0; i < N; i++) {
        if (getD(0, i) > maxDist) {
            maxDist = getD(0, i);
            u = i;
        }
    }

    maxDist = -1;
    for (int i = 0; i < N; i++) {
        if (getD(u, i) > maxDist) {
            maxDist = getD(u, i);
            v = i;
        }
    }

    int radius = inf;
    int d1 = -1, d2 = -1;
    for (int i = 0; i < N; i++) {
        int distFromHubToU = (getD(u, i) + getD(u, 0) - getD(i, 0))/2;
        int distFromHubToV = getD(u, v) - distFromHubToU;
        if (max(distFromHubToU, distFromHubToV) < radius) {
            radius = max(distFromHubToU, distFromHubToV);
            d1 = distFromHubToU;
            d2 = -1;
        } else if (max(distFromHubToU, distFromHubToV) == radius) {
            if (distFromHubToU != d1) {
                d2 = distFromHubToU;
            }
        }
    }
    if (d2 != -1 && d1 > d2) swap(d1, d2);

    bool balanced = true;
    map<int, int> frequency;
    for (int i = 0; i < N; i++) {
        int distFromU = (getD(u, i) + getD(u, 0) - getD(0, i))/2;
        frequency[distFromU]++;
    }

    int ct1 = 0;
    int ct2 = 0;
    for (auto x : frequency) {
        if (x.f <= d1) ct1 += x.s;
        if (x.f <= d2) ct2 += x.s;
    }
    bool isHub2 = false;
    if (ct1 - frequency[d1] > N/2) balanced = false;
    if (ct1 < N/2) {
        if (d2 != -1) {
            if (ct2 - frequency[d2] <= N/2 && ct2 >= N/2) {
                isHub2 = true;
            }
            else balanced = false;
        } else {
            balanced = false;
        }
    }
    if (balanced) {
        int distToHub = -1;
        if (isHub2) {
            distToHub = d2;
        } else {
            distToHub = d1;
        }
        vector<int> nodes;
        for (int i = 0; i < N; i++) {
            int distFromU = (getD(u, i) + getD(u, 0) - getD(0, i))/2;
            if (distFromU != distToHub) continue;
            nodes.pb(i);
        }

        int tgt = 0;
        vector<int> stackA, stackB;
        stackB.pb(0);
        for (int i = 0; i < nodes.size() - 1; i++) {
            int a = nodes[tgt], b = nodes[i+1];
            bool same = getD(a, u) + getD(b, u) - getD(a, b) != distToHub*2;
            if (same) {
                stackB.pb(i+1);
            } else {
                stackA.pb(stackB.back());
                stackB.pop_back();
                if (stackB.empty()) {
                    tgt = i+1;
                    stackB.pb(i+1);
                } else {
                    stackA.pb(i+1);
                }
            }
        }
        if (tgt < nodes.size()) {
            int sz = stackB.size();
            while (!stackA.empty()) {
                int x = stackA.back();
                stackA.pop_back();
                int a = nodes[x], b = nodes[tgt];
                bool same = getD(a, u) + getD(b, u) - getD(a, b) != distToHub*2;
                if (same) {
                    sz++;
                    if (!stackA.empty()) stackA.pop_back();
                } else {
                    if (stackB.empty()) break;
                    stackB.pop_back();
                }
            }
            if (sz > N/2) balanced = false;
        }
    }

    return (balanced ? 1 : -1) * radius;
}
