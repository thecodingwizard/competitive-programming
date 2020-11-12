#include <stdio.h>
#include <stdlib.h>
#include "wombats.h"

#define fail(s, x...) do { \
		fprintf(stderr, s "\n", ## x); \
		exit(1); \
	} while(0)

static int H[5000][200];
static int V[5000][200];

int main() {
	int R, C, E, P, Q, W, V1, V2, event, i, j;
	int res;

	FILE *f = fopen("wombats.in", "r");
	if (!f)
		fail("Failed to open input file.");

	res = fscanf(f, "%d%d", &R, &C);
    for (i = 0; i < R; ++i)
        for (j = 0; j < C-1; ++j)
            res = fscanf(f, "%d", &H[i][j]);
    for (i = 0; i < R-1; ++i)
        for (j = 0; j < C; ++j)
            res = fscanf(f, "%d", &V[i][j]);

    init(R, C, H, V);

	res = fscanf(f, "%d", &E);
	for (i = 0; i < E; i++) {
		res = fscanf(f, "%d", &event);
        if (event == 1) {
            res = fscanf(f, "%d%d%d", &P, &Q, &W);
            changeH(P, Q, W);
        } else if (event == 2) {
            res = fscanf(f, "%d%d%d", &P, &Q, &W);
            changeV(P, Q, W);
        } else if (event == 3) {
            res = fscanf(f, "%d%d", &V1, &V2);
            printf("%d\n", escape(V1, V2));
        } else
            fail("Invalid event type.");
	}

	fclose(f);
	return 0;
}
