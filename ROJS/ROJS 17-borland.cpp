#include <bits/stdc++.h>

using namespace std;

#define ll long long

int s, a, b, c, invA; 
const int mod = 1e9+7;

int right(int n) {
    return ((ll)a*n+b)%c;
}
int left(int n) {
    return ((ll)(n-b+c)%c*invA)%c;
}

int solve(int l, int r, int first) {
    if (l > r) return 0;

    int mid = (l+r)/2;
    int num = first;
    for (int i = l; i < mid; i++) {
        num = right(num);
    }

    int ans = (solve(l, mid-1, first) + solve(mid+1, r, right(num))) % mod;

    int lptr = mid, rptr = mid;
    int leftMax = 0, leftNum = num, rightNum = num, rMax = 0;
    while (lptr >= l) {
        leftMax = max(leftMax, leftNum);
        while (rptr + 1 <= r && right(rightNum) <= leftMax) {
            rptr++;
            rightNum = right(rightNum);
            rMax = max(rMax, rightNum);
            ans = ((ll)ans + (ll)rMax*(mid-lptr))%mod;
        }

        ans = ((ll)ans + (ll)leftMax*(rptr-mid+1))%mod;

        lptr--;
        leftNum = left(leftNum);
    }
    rMax = 0;
    while (rptr + 1 <= r) {
        rightNum = right(rightNum);
        rMax = max(rMax, rightNum);
        rptr++;
        ans = ((ll)ans + (ll)rMax*(mid-l+1))%mod;
    }
    return ans;
}

int main() {
    int n; cin >> n >> s >> a >> b >> c;

    invA = 1;
    int pwr = c-2;
    int base = a;
    while (pwr) {
        if (pwr & 1) invA = ((ll)invA*base) % c;
        pwr >>= 1;
        base = ((ll)base*base)%c;
    }

    cout << solve(0, n-1, s) << endl;
}
