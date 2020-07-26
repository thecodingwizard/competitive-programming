#include <bits/stdc++.h>

using namespace std;

int main() {

    int n;
    cin >> n;

    int A[n];
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    sort(A, A+n);

    int answer = 1;

    for (int i = 0; i < n - 1; ++i) {
        if (A[i] != A[i + 1]) {
            answer++;
        }
    }

    cout << answer << endl;

    return 0;
}
