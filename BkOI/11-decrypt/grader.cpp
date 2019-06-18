#include "decrypt.h"
#include <bits/stdc++.h>
using namespace std;

static int R[3];
static int M[256];
static int ct = 0;

int query(int x) {
	if (x < 0 || x >= 256) {
		printf("Query out of bounds!\n");
		exit(0);
	}
	ct++;
	if (ct > 320) {
		printf("Used more than 320 queries!\n");
		exit(0);
	}
	int ret = M[x^R[0]];
	int t = R[0]^R[1];
	R[0] = R[1];
	R[1] = R[2];
	R[2] = t;
	return ret;
}

void solution(int _R[], int _M[]) {
	for (int i = 0; i < 3; i++) printf("%d\n", _R[i]);
	for (int i = 0; i < 256; i++) printf("%d\n", _M[i]);
}

int main () {
	for (int i = 0; i < 3; i++) scanf("%d", &R[i]);
	for (int i = 0; i < 256; i++) scanf("%d", &M[i]);
	decrypt();
	cout << "Used " << ct << " queries." << endl;
	return 0;
}
