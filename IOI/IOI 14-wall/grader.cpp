#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "wall.h"

int main()
{
  int n;
  int k;

  int i, j;  
  int status = 0;

  status = scanf("%d%d", &n, &k);
  assert(status == 2);

  int* op = (int*)calloc(sizeof(int), k);
  int* left = (int*)calloc(sizeof(int), k);
  int* right = (int*)calloc(sizeof(int), k);
  int* height = (int*)calloc(sizeof(int), k);
  int* finalHeight = (int*)calloc(sizeof(int), n);

  for (i = 0; i < k; i++){
    status = scanf("%d%d%d%d", &op[i], &left[i], &right[i], &height[i]);
    assert(status == 4);
  }

  buildWall(n, k, op, left, right, height, finalHeight);

  for (j = 0; j < n; j++)
    printf("%d\n", finalHeight[j]);
  
  return 0;
}
