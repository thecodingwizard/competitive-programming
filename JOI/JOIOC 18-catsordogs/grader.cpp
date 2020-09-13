#include "catdog.h"
#include <cstdio>
#include <cassert>
#include <vector>
#include <stdlib.h>

int readInt(){
	int i;
	if(scanf("%d",&i)!=1){
		fprintf(stderr,"Error while reading input\n");
		exit(1);
	}
	return i;
}

int main(){
	int N=readInt();
	
	std::vector<int> A(N-1),B(N-1);
	for(int i=0;i<N-1;i++)
	{
		A[i]=readInt();
		B[i]=readInt();
	}
	int Q;
	assert(scanf("%d",&Q)==1);
	std::vector <int> T(Q),V(Q);
	for(int i=0;i<Q;i++)
	{
		T[i]=readInt();
		V[i]=readInt();
	}
	
	initialize(N,A,B);
	
	std::vector<int> res(Q);
	for(int j=0;j<Q;j++)
	{
		if(T[j]==1) res[j]=cat(V[j]);
		else if(T[j]==2) res[j]=dog(V[j]);
		else res[j]=neighbor(V[j]);
	}
	for(int j=0;j<Q;j++)
		printf("%d\n",res[j]);
	return 0;
}
