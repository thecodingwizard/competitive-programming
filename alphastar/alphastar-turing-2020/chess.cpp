#include <bits/stdc++.h>

#define MOD 1000000007
#define MAX_N 100005
#define f first
#define s second

using namespace std;

struct matrix {
    long double ar[2][2];
};

matrix st, c, tmp;

matrix mult(matrix a, matrix b) {
    for (int i = 0; i < 2; i ++)
        for (int j = 0; j < 2; j ++)
            c.ar[i][j] = 0.0;

    for (int i = 0; i < 2; i ++)
        for (int j = 0; j < 2; j ++)
            for (int k = 0; k < 2; k ++)
                c.ar[i][j] = (c.ar[i][j] + ((a.ar[i][k] * b.ar[k][j])));

    return (c);
}

matrix fast_exp (long long ind, matrix a) {
    if (ind == 1) { return (a); }
    if (ind % 2) {
        return (mult(a, fast_exp(ind - 1, a)));
    }

    else {
        tmp = fast_exp(ind / 2, a);
        return (mult(tmp, tmp));
    }
}

int N;
long double A, B, C, D;

void solve(int xxxx) {
    cin >> N;
    cin >> A >> B >> C >> D;


    if (C > D) {
    st.ar[0][0] = C;
    st.ar[0][1] = D;
    st.ar[1][0] = 1.0 - C;
    st.ar[1][1] = 1.0 - D;
    } else {
    st.ar[1][0] = C;
    st.ar[1][1] = D;
    st.ar[0][0] = 1.0 - C;
    st.ar[0][1] = 1.0 - D;
    }

    matrix a;
    
    if (N == 1) {
        cout << "Case #" << xxxx << ": " << fixed << setprecision(6) << A << endl;
        return;
    }
    
    if (N == 2) {
        a.ar[0][0] = 1;
        a.ar[1][0] = 0;
    }else if (N > 2)
        a = fast_exp(N - 2, st);
    
    long double white = a.ar[0][0] * C + a.ar[1][0] * D;

    cout << "Case #" << xxxx << ": " << fixed << setprecision(6) << white * max(A, B) + (1.0 - white) * min(A, B) << endl;

    return;
}

int main() {
    int T;
    cin >> T;
    
    for (int i = 0; i < T; i ++)    
        solve(i + 1);
}
