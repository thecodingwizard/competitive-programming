#include <bits/stdc++.h>

using namespace std;

int A[100];
int n;

int val = 0;
int tgt = 0;
bool good = false;
void solve(int x) {
  if (val == A[tgt]) good = true;
  if (x == n) {
    return;
  }
  solve(x+1);
  if (tgt != x) {
    val += A[x];
    solve(x+1);
    val -= A[x];
    val -= A[x];
    solve(x+1);
    val += A[x];
  }
}

int main() {
  int t; cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> A[i];
    }
    good = false;
    for (int i = 0; i < n; i++) {
      val = 0;
      tgt = i;
      solve(0);
    }
    if (good) cout << "YES" << endl;
    else cout << "NO" << endl;
  }
  return 0;
}