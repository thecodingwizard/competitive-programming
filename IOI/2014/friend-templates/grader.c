#include <stdio.h>
#include <assert.h>
#define __MAXSIZE__ 100002
#include "friend.h"

// Confidence
int confidence[__MAXSIZE__];

// Host
int host[__MAXSIZE__];

// Protocol
int protocol[__MAXSIZE__];

// Main
int main(void)
{
	int n,i;

	// Number of people
	assert(scanf("%d",&n)==1);
	
	// Confidence
	for(i=0;i<n;i++)
		assert(scanf("%d",&confidence[i])==1);
	
	// Host and Protocol
	for(i=1;i<n;i++)
		assert(scanf("%d %d",&host[i],&protocol[i])==2);
	
	// Answer
	printf("%d\n",findSample(n,confidence,host,protocol));
	return 0;
}
