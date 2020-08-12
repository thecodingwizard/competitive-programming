#include<bits/stdc++.h>
#include "grader.h"

using namespace std;

static int maxQ = 0;
static vector < int > theRealAnswer;

bool isSubsequence (vector < int > v)
{
    if (v.size () > maxQ)
        maxQ = v.size ();
    int i = 0;
    for (auto it : v)
    {
        while (i < theRealAnswer.size () && it != theRealAnswer[i]) i ++;
        if (i == theRealAnswer.size ()) return 0;
        i ++;
    }
    return 1;
}

int main ()
{
int n, x;
scanf ("%d", &n), maxQ = 0;
for (int i=1; i<=n; i++)
    scanf ("%d", &x), theRealAnswer.push_back (x);

vector < int > ans = findSequence (n);
if (ans.size () != theRealAnswer.size ())
{
    printf ("Different lengths\n");
    for (auto it : ans)
        printf ("%d ", it);
    printf ("\n");
    return 0;
}

for (int i=0; i<ans.size (); i++)
    if (ans[i] != theRealAnswer[i])
    {
        printf ("WA position %d\n", i + 1);
        for (auto it : ans)
            printf ("%d ", it);
        printf ("\n");
        return 0;
    }
printf ("Ok, biggest queried length %d\n", maxQ);
return 0;
}

