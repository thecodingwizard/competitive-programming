#include "grader.h"
#include "encoder.h"
#include "decoder.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static int h[1000][1000], hcnt;

#define FOR(i,n) for (int i = 0; i < (n); i++)

static int bits[16000000], nb;
static int curbit = 0;

void encode_bit(int bit) {
 bits[nb++] = bit;
}

int decode_bit() {
 if (curbit >= nb) {
    exit(92);
 }
 return bits[curbit++];
}

void hops(int a, int b, int d) {
   if (h[a][b] != d) {
      exit(92);
   }
   h[a][b] = -1;
   hcnt++;
}

static int nv, ne, c;
static int v1[1234567], v2[1234567];

/* and here is the driver */
int main(int argc, char **argv) {
 assert(3 == scanf("%i%i%i", &nv, &ne, &c));
 FOR(i,ne) assert(2 == scanf("%i%i", v1+i, v2+i));
 for (int i=0;i<c;i++) for (int j=0;j<nv;j++) scanf("%d",&h[i][j]);
 encode(nv, c, ne, v1, v2);
 decode(nv, c);
 if (hcnt != c*nv) {
    exit(92);
 }
 printf("%s 1\n",nb<=16000000?"OK":"NO");
 printf("%s 2\n",nb<=360000?"OK":"NO");
 printf("%s 3\n",nb<=80000?"OK":"NO");
 printf("%s 4\n",nb<=70000?"OK":"NO");
}
