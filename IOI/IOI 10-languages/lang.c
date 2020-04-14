#include <stdlib.h>
#include <stdio.h>

#include "grader.h"
#include "lang.h"

#define SZ 100

int prev[1100000];

void excerpt(int *E) {
   prev[E[0]] = language(prev[E[0]]);
}
