#include <iostream>
#include <string>
#include <utility>

#define INF 1000000000

using namespace std;

int N, n;
char big[500][500], small[500][500];

void run() {
    int count = 0;
    for (int i = 0; i <= N - n; i++) {
        for (int j = 0; j <= N - n; j++) {
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    if (small[k][l] != big[i+k][j+l]) {
                        goto bad;
                    }
                }
            }
            count++;

            bad:
            continue;
        }
    }

    char tmp[n][n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            tmp[i][j] = small[n-j-1][i];
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            small[i][j] = tmp[i][j];
    }

    cout << count;
}

int main() {
    while (cin >> N >> n && (N || n)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> big[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> small[i][j];
            }
        }

        run();
        cout << " ";
        run();
        cout << " ";
        run();
        cout << " ";
        run();
        cout << endl;
    }

    return 0;
}