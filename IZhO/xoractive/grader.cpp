#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

namespace {
    const int MAX_VALUE_OF_N = 100;
    const int MAX_VALUE_OF_Q = 200;
    int numberOfQueries = 0;
    int n;
    std::vector<int> a;

    void wrong_answer(const char *MSG) {
        printf("-1\n");
        exit(0);
    }
}

void query() {
    numberOfQueries++;

    if (numberOfQueries > MAX_VALUE_OF_Q) {
        wrong_answer("Number of queries exceeded");
    }
}

int ask(int position) {
    query();

    if (position < 1 || position > n) {
        wrong_answer("Not correct position");
    }
    return a[position - 1];

}
vector<int> get_pairwise_xor(vector<int> positions) {
    query();

    if (positions.empty() || positions.size() > n) {
        wrong_answer("Not correct size");
    }

    sort(positions.begin(), positions.end());

    for (int i = 1; i < positions.size(); i++) {
        if (positions[i] == positions[i - 1]) {
            wrong_answer("Not unique");
        }
    }

    for (int i = 0; i < positions.size(); i++) {
        if (positions[i] < 1 || positions[i] > n) {
            wrong_answer("Not correct position");
        }
    }

    vector<int> pairwise_xor;

    for (int i = 0; i < positions.size(); i++) {
        for (int j = 0; j < positions.size(); j++) {
            pairwise_xor.push_back(a[positions[i] - 1] ^ a[positions[j] - 1]);
        }
    }
    sort(pairwise_xor.begin(), pairwise_xor.end());

    return pairwise_xor;
}


vector<int> guess(int n);

int main() {
    assert(scanf("%d", &n) == 1);

    assert(1 <= n && n <= MAX_VALUE_OF_N);

    for (int i = 1; i <= n; i++) {
        int x;

        assert(scanf("%d", &x) == 1);
        assert(x >= 0 && x <= 1000 * 1000 * 1000);

        a.push_back(x);
    }
    vector<int> participant_solution = guess(n);

    if (participant_solution.size() != n) {
        wrong_answer("-1");
    }

    printf("%d\n", n);

    for (auto i: participant_solution) {
        printf("%d ", i);
    }
    printf("\n");
    printf("%d\n", numberOfQueries);
    return 0;
}
