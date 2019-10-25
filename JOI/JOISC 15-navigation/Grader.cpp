#include "Anna.h"
#include "Annalib.h"
#include "Bruno.h"
#include "Brunolib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N (100000)
#define MAX_N_2 (100001)

static int N;
static int S;
static int T;
static int K;
static int A[MAX_N];
static int B[MAX_N];
static int P[MAX_N];
static int Q[MAX_N];

static int flag_built[MAX_N_2];
static int flag_value[MAX_N_2];

static int A_[MAX_N];
static int B_[MAX_N];
static int P_[MAX_N];
static int Q_[MAX_N];

static int called_Answer;
static int L;

static int V_max;

static int Y;

static void Wrong(int message) {
  printf("Wrong Answer [%d]\n", message);
  exit(1);
}

void Flag(int I, int V) {
  if (I < 1 || I > N) {
    Wrong(1);
  }
  if (flag_built[I] != 0) {
    Wrong(2);
  }
  if (V < 0 || V > N) {
    Wrong(3);
  }

  flag_built[I] = 1;
  flag_value[I] = V;

  if (V_max < V) {
    V_max = V;
  }
}

void Answer(int X) {
  int find_on_P = 0;
  int i;
  if (called_Answer == 1) {
    Wrong(6);
  }
  called_Answer = 1;

  for (i = 0; i < L; ++i) {
    if (P[i] == X) {
      find_on_P = 1;
    }
  }
  if (find_on_P == 0 && X != S) {
    Wrong(5);
  }

  if (T == S) {
    if (X != Y) {
      Wrong(8);
    }
  } else if (X != Y) {
    Wrong(9);
  }
}

int main(void) {
  int i;
  if (scanf("%d%d%d%d", &N, &S, &T, &K) != 4) {
    fprintf(stderr, "error: cannot read N, S, T and K.\n");
    exit(1);
  }
  if (N < 2 || MAX_N < N) {
    fprintf(stderr, "error: N is out of bounds.\n");
    exit(1);
  }
  if (S < 1 || N < S) {
    fprintf(stderr, "error: S is out of bounds.\n");
    exit(1);
  }
  if (T < 1 || N < T) {
    fprintf(stderr, "error: T is out of bounds.\n");
    exit(1);
  }
  if (K < 1 || K > 4) {
    fprintf(stderr, "error: K is out of bounds.\n");
    exit(1);
  }

  for (i = 0; i < N - 1; ++i) {
    if (scanf("%d%d", &A[i], &B[i]) != 2) {
      fprintf(stderr, "error: cannot read A[%d] and B[%d].\n", i, i);
      exit(1);
    }
    if (A[i] < 1 || N < A[i]) {
      fprintf(stderr, "error: A[%d] is out of bounds.\n", i);
      exit(1);
    }
    if (B[i] < 1 || N < B[i]) {
      fprintf(stderr, "error: B[%d] is out of bounds.\n", i);
      exit(1);
    }
  }
  if (scanf("%d", &Y) != 1) {
    fprintf(stderr, "error: cannot read Y.\n");
    exit(1);
  }

  V_max = 0;

  memcpy(A_, A, sizeof(A));
  memcpy(B_, B, sizeof(B));
  Anna(K, N, T, A_, B_);

  for (i = 1; i <= N; ++i) {
    if (flag_built[i] == 0) {
      Wrong(4);
    }
  }

  for (i = 0; i < N - 1; ++i) {
    if (A[i] == S) {
      P[L] = B[i];
      Q[L] = flag_value[B[i]];
      ++L;
    }
    if (B[i] == S) {
      P[L] = A[i];
      Q[L] = flag_value[A[i]];
      ++L;
    }
  }
  memcpy(P_, P, sizeof(P));
  memcpy(Q_, Q, sizeof(Q));

  Bruno(K, S, flag_value[S], L, P_, Q_);

  if (called_Answer == 0) {
    Wrong(7);
  }

  printf("Accepted : V_max = %d\n", V_max);

  return 0;
}

