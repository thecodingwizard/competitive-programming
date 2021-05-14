#include <bits/stdc++.h>
#include "gap.h"

using namespace std;

#define f first
#define s second
#define ll long long
#define ii pair<ll, ll>

ii get(ll a, ll b) {
    b = min(b, (ll)1e18);
    ii x;
    MinMax(a, b, &x.f, &x.s);
    return x;
}

long long findGap(int T, int N)
{
    if (T == 1) {
        vector<ll> nums, nums2;
        ii range = make_pair(1, (ll)1e18);
        for (int i = 0; i < (N+1)/2; i++) {
            if (range.f > range.s) break;
            ii res = get(range.f, range.s);
            if (res.f == -1) break;
            nums.push_back(res.f); nums2.push_back(res.s);
            range = make_pair(res.f+1, res.s-1);
        }
        reverse(nums2.begin(), nums2.end());
        for (ll x : nums2) nums.push_back(x);
        ll best = 0;
        for (int i = 0; i < (int)nums.size() - 1; i++) {
            best = max(best, nums[i+1] - nums[i]);
        }
        return best;
    }


    ii boundary = get(1, 1e18);
    ll block = (boundary.s-boundary.f)/(N-1);
    ll prev = boundary.f;

    ll ans = 0;
    for (ll cur = boundary.f + 1; cur < boundary.s; cur += block + 1) {
        ii thing = get(cur, cur+block);
        if (thing.f == -1) continue;
        ans = max(ans, thing.f - prev);
        prev = thing.s;
    }

    ans = max(ans, boundary.s - prev);

    return ans;
}
