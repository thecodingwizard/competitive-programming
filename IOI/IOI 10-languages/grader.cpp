#include "grader.h"
#include "lang.h"

#include <bits/stdc++.h>
using namespace std;
#define N 100

static char lang[20], lan[100][20];
static int lnum, i,j,k,n,nl, uni[N], correct, tot;
int wrong[56];
int total[56];
int language(int L) {
   if (L < 0 || L >= 56) exit(92);
   correct += (L == lnum);
   tot++;
   if (L != lnum) {
       wrong[lnum]++;
   }
   total[lnum]++;
   return lnum;
}

int main(){
   for (n=0; 1 == scanf("%s",lang); n++) {
      for (i=0;i<nl && strcmp(lang,lan[i]);i++);
      strcpy(lan[i],lang);
      if (i == nl) {
         nl++;
      }
      //cout << lang << " " << i << endl;
      lnum = i;
      for (i=0;i<N;i++) scanf("%d,",&uni[i]);
      if (lnum == 45) {
        //for (int j = 0; j < 100; j++) cout << uni[j] << " ";
        //cout << endl;
      }
      scanf("%*[^\n]");
      excerpt(uni);
   }
   printf("OK %0.2lf%%\n",100.0*correct/tot);
   /*
   for (int i = 0; i <= 55; i++) {
       cout << "Language " << i << ": " << 100.0*wrong[i]/total[i] << endl;
   }
   */
   return 0;
}
