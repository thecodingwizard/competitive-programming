#include "wiring.h"

#include <cassert>
#include <cstdio>

using namespace std;

int main() {
	int n, m;
	assert(2 == scanf("%d %d", &n, &m));

	vector<int> r(n), b(m);
	for(int i = 0; i < n; i++)
		assert(1 == scanf("%d", &r[i]));
	for(int i = 0; i < m; i++)
		assert(1 == scanf("%d", &b[i]));

	long long res = min_total_length(r, b);
	printf("%lld\n", res);

	return 0;
}
