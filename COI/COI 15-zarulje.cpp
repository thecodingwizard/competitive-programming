/*
 * For a given starting position, note that we only care about the nonincreasing sequence of numbers to the left and to the right of it.
 * We can disregard numbers that are decreasing because we must take those numbers so they won't increase the number of ways.
 *
 * If we have something like (some number smaller than 7), 7, 7, 7, [Our current position], 7, 7, (some number less than 7)
 * Where there's a of the same number to the left of our current position and b of the same number to the right, then
 * we have (a+b) choose (a) ways to take those numbers.
 *
 * Therefore, it suffices to loop through all the numbers i from 1 to 200,000. Let's say there are a i's to the left of our
 * starting position in the nonincreasing sequence, and b i's to the right. Then, we multiply the number of ways by (a+b) choose a.
 *
 * To solve the third subtask, we simply sweep from left to right and move our starting position leftward by one step each time.
 * As we progress, we update the nonincreasing sequences to the left and to the right of our starting positions.
 * For any numbers that change as a result of updating the nonincreasing sequences, we update our answer accordingly by
 * dividing by the previous contribution of the number and multiplying by the new contribution of the number.
 */

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int mod = 1000000007;

int ctLeft[200001], ctRight[200001];
bool included[200001];
int ans[200001];
int change[200001];
ll fac[200001];

ll power(ll x, int y, int p)
{ 
    ll res = 1; // Initialize result 
  
    x = x % p; // Update x if it is more than or 
    // equal to p 
  
    while (y > 0) { 
        // If y is odd, multiply x with result 
        if (y & 1) 
            res = (res * x) % p; 
  
        // y must be even now 
        y = y >> 1; // y = y/2 
        x = (x * x) % p; 
    } 
    return res; 
}

ll inv(ll x) {
    return power(x, mod-2, mod);
}

// calculate addition to ans based on x
// make sure to update change
ll calc(int x) {
    if (ctLeft[x] > 0 && ctRight[x] > 0) {
        //cout << "changing " << x << " = " << ctLeft[x] << ", " << ctRight[x] << endl;
        return change[x] = fac[ctLeft[x]+ctRight[x]] * inv(fac[ctRight[x]]) % mod * inv(fac[ctLeft[x]]) % mod;
    } else {
        return change[x] = 1;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    int A[n]; for (int i = 0; i < n; i++) cin >> A[i];

    for (int i = 0; i <= 200000; i++) {
        fac[i] = i == 0 ? 1 : (fac[i-1]*i)%mod;
    }

    int nextRight[n];
    stack<int> s;
    for (int i = 0; i < n; i++) {
        nextRight[i] = n;
        while (!s.empty() && A[s.top()] >= A[i]) {
            nextRight[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }

    s = stack<int>();

    set<int> changed;
    ll runningAns = 1;
    for (int i = 0; i < n; i++) {
        //cout << "i is " << i << endl;
        int rptr = i+1;
        while (rptr < n && !included[rptr]) {
            included[rptr] = true;
            ctRight[A[rptr]]++;
            changed.insert(A[rptr]);
            rptr = nextRight[rptr];
        }
        if (i != 0) {
            int prevptr = i;
            while (prevptr < n && prevptr != rptr) {
                included[prevptr] = false;
                ctRight[A[prevptr]]--;
                changed.insert(A[prevptr]);
                prevptr = nextRight[prevptr];
            }
        }
        for (int c : changed) {
            //cout << "upd " << c << endl;
            runningAns = (runningAns * (change[c] == 0 ? 1 : inv(change[c])) % mod * calc(c)) % mod;
            //cout << c << ": " << change[c] << endl;
        }

        ans[i] = runningAns;
        
        changed.clear();
        while (!s.empty() && A[s.top()] > A[i]) {
            ctLeft[A[s.top()]]--;
            changed.insert(A[s.top()]);
            s.pop();
        }
        ctLeft[A[i]]++;
        changed.insert(A[i]);
        s.push(i);
    }

    for (int i = 0; i < k; i++) {
        int x; cin >> x; --x;
        cout << ans[x] << "\n";
    }

    return 0;
}
