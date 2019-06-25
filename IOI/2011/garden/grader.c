#include "garden.h"
#include "gardenlib.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_M  1000000
#define MAX_Q  2000

static int N, M, P, Q;
static int R[MAX_M][2];
static int G[MAX_Q];
static int solutions[MAX_Q];
static int answers[MAX_Q];
static int answer_count;

inline 
void my_assert(int e) {if (!e) abort();}
void read_input()
{
  int i;
  my_assert(3==scanf("%d %d %d",&N,&M,&P));
  for(i=0; i<M; i++)
    my_assert(2==scanf("%d %d",&R[i][0],&R[i][1]));
  my_assert(1==scanf("%d",&Q));
  for(i=0; i<Q; i++)
    my_assert(1==scanf("%d",&G[i]));
  for(i=0; i<Q; i++)
    my_assert(1==scanf("%d",&solutions[i]));
}

void answer(int x)
{
  if(answer_count>=Q) {
    printf("Incorrect.  Too many answers.\n");
    exit(0);
  }
  answers[answer_count] = x;
  answer_count++;
}

int main()
{
  int correct, i;

  read_input();
  answer_count = 0;
  count_routes(N,M,P,R,Q,G);

  if(answer_count!=Q) {
    printf("Incorrect.  Too few answers.\n");
    exit(0);
  }

  correct = 1;
  for(i=0; i<Q; i++)
    if(answers[i]!=solutions[i])
      correct = 0;
  if(correct)
    printf("Correct.\n");
  else {
    printf("Incorrect.\n");
    printf("Expected: ");
    for(i=0; i<Q; i++)
      printf("%d ",solutions[i]);
    printf("\nReturned: ");
    for(i=0; i<Q; i++)
      printf("%d ",answers[i]);
  }
  return 0;
}
