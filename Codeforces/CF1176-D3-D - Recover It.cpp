#include <bits/stdc++.h>

using namespace std;

template<class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define F0R1(i, a) for (int i=1; i<=(a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
#define F0Rd1(i, a) for (int i=a; i>0; i--)
#define SORT(vec) sort(vec.begin(), vec.end())
#define RSORT(vec) sort(vec.rbegin(), vec.rend())
#define MIN(a, b) a = min(a, b)
#define MAX(a, b) a = max(a, b)

#define INF 1000000010
#define LL_INF 4500000000000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define pA first
#define pB second
#define mp make_pair
#define pb push_back
#define PI acos(-1.0)
#define ll long long
#define MOD (int)(2e+9+11)
#define SET(vec, val, size) for (int i = 0; i < size; i++) vec[i] = val;
#define SET2D(arr, val, dim1, dim2) F0R(i, dim1) F0R(j, dim2) arr[i][j] = val;
#define SET3D(arr, val, dim1, dim2, dim3) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) arr[i][j][k] = val;
#define SET4D(arr, val, dim1, dim2, dim3, dim4) F0R(i, dim1) F0R(j, dim2) F0R(k, dim3) F0R(l, dim4) arr[i][j][k][l] = val;
#define READGRID(arr, dim) F0R(i, dim) F0R(j, dim) cin >> arr[i][j];
#define all(x) (x).begin(), (x).end()

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef vector<ll> vl;

void setupIO(const string &PROB = "") {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (PROB.length() != 0) {
        ifstream infile(PROB + ".in");
        if (infile.good()) {
            freopen((PROB + ".in").c_str(), "r", stdin);
            freopen((PROB + ".out").c_str(), "w", stdout);
        }
    }
}

/* ============================ */

bool isPrime[3000000];
vi primes;

int child[3000000];
int parent[3000000];

vi ans;

int gd(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return n / i;
        }
    }
    assert(false);
}

int main() {
    setupIO();

    int n; cin >> n;
    int A[2*n];
    multiset<int> nums;
    F0R(i, 2*n) {
        cin >> A[i];
        nums.insert(A[i]);
        child[A[i]] = -1;
    }

    SET(isPrime, true, 3000000);
    SET(child, -1, 3000000);
    SET(parent, -1, 3000000);
    for (int i = 2; i < 3000000; i++) {
        if (isPrime[i]) {
            for (int j = i; j < 3000000; j += i) isPrime[j] = false;
            isPrime[i] = true;
            primes.pb(i);
        }
    }

    for (int i = 0; i < 2*n; i++) {
        int num = A[i];
        if (isPrime[num]) {
            if (num <= 199999) {
                child[num] = primes[num - 1];
                parent[child[num]] = num;
            }
        } else {
            child[num] = gd(num);
        }
    }

    int iterations = 0;
    while (!nums.empty()) {
        iterations++;
        assert(iterations < n+5);
        auto it = --nums.end();
        int itVal = *it;
        if (isPrime[itVal]) {
            assert(parent[itVal] != -1);
            ans.pb(parent[itVal]);
            nums.erase(it);
            nums.erase(nums.find(parent[itVal]));
        } else {
            assert(child[itVal] != -1);
            ans.pb(itVal);
            nums.erase(it);
            nums.erase(nums.find(child[itVal]));
        }
        assert(nums.size() % 2 == 0);
    }

    cout << ans[0];
    for (int i = 1; i < n; i++) cout << " " << ans[i];
    cout << endl;

    return 0;
}