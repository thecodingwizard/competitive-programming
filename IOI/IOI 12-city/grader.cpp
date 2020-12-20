
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define inbuf_len 1 << 16
#define outbuf_len 1 << 16

int DistanceSum(int N, int *X, int *Y);

int main() {
  int tmp;

  /* Set input and output buffering */
  char *inbuf, *outbuf;
  inbuf = (char*) malloc(inbuf_len * sizeof(char));
  outbuf = (char*) malloc(outbuf_len * sizeof(char));
  tmp = setvbuf(stdin, inbuf, _IOFBF, inbuf_len);
  assert(tmp == 0);
  tmp = setvbuf(stdout, outbuf, _IOFBF, outbuf_len);
  assert(tmp == 0);

  int N, i;
  tmp = scanf("%d", &N);
  assert(tmp == 1);
  int *sq_x, *sq_y;
  sq_x = (int*) malloc(N * sizeof(int));
  sq_y = (int*) malloc(N * sizeof(int));
  for (i = 0; i < N; i++) {
    tmp = scanf("%d %d", &sq_x[i], &sq_y[i]);
    assert(tmp == 2);
  }
  int ds = DistanceSum(N, sq_x, sq_y);
  printf("%d\n", ds);

  return 0;

}
