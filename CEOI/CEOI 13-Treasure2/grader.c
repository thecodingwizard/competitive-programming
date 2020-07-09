#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "treasure.h"

typedef long long ll;

void findTreasure (int N);

static int N;
static char A[105][105];
static int S[105][105];
static char Chk[105][105];
static ll K;
static int treasure_cells;

void my_assert (int a, const char* s) {
    if(!a) {
        puts(s);
        exit(0);
    }
}

int countTreasure (int r1, int c1, int r2, int c2) {
    if(!(1 <= r1 && r1 <= r2 && r2 <= N && 1 <= c1 && c1 <= c2 && c2 <= N)) {
        printf("check the range of the parameters of countTreasure() : r1 = %d, c1 = %d, r2 = %d, c2 = %d", r1, c1, r2, c2);
        exit(0);
    }
	my_assert(treasure_cells == 0, "you cannot call countTreasure() after calling Report()");
    K += 1 + N*N - (r2 - r1 + 1) * (c2 - c1 + 1);
    return S[r2][c2] - S[r2][c1-1] - S[r1-1][c2] + S[r1-1][c1-1];
}

void Report (int r, int c) {
    printf("Reported r = %d, c = %d\n", r, c);
    if(!(1 <= r && r <= N && 1 <= c && c <= N)) {
        printf("check the range of the parameters of Report() : r = %d, c = %d", r, c);
        exit(0);
    }
    if(A[r][c] != 1) {
        printf("no treasure at (r, c) : r = %d, c = %d", r, c);
        exit(0);
    }
    if(Chk[r][c]) {
        printf("already reported (r, c) : r = %d, c = %d", r, c);
        exit(0);
    }
    ++treasure_cells;
    Chk[r][c] = 1;
}

int main() {
    int i, j;
    
    my_assert(scanf("%d", &N) == 1, "the first line of the input must be an integer N (1 <= N <= 100)");
    my_assert(1 <= N && N <= 100, "check the range of N : 1 <= N <= 100");
    
    for(i = 1; i <= N; i++) {
        my_assert(scanf("%s", A[i]+1) == 1, "the second~(N+1)th line must contain a N x N sized map");
        my_assert(strlen(A[i]+1) == N, "each line of the map must contain N zeroes or ones (before loop)");
        for(j = 1; j <= N; j++) {
            my_assert(A[i][j] == '0' || A[i][j] == '1', "each line of the map must contain N zeroes or ones (in loop)");
            A[i][j] -= '0';
            S[i][j] = S[i-1][j] + S[i][j-1] - S[i-1][j-1] + A[i][j];
        }
    }
    
    findTreasure(N);
    
    my_assert(treasure_cells == S[N][N], "not all of the treasure cells have been reported");
    
    printf("Successful : N = %d, K = %lld\n", N, K);
    
    int score = 0;
    if(K <= 7. / 16. * N*N*N*N + N*N) score = 10;
    else if(K <= 7. / 16. * N*N*N*N + 2*N*N*N) score = 8;
    else if(K <= 3. / 4. * N*N*N*N) score = 4;
    else if(K <= (ll)N*N*N*N) score = 1;
    
    printf("score = %d\n", score);
    
    return 0;
}
