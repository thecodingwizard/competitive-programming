#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <algorithm>
#include <random>
using namespace std;

#define MAX_N 1000
#define MAX_V 1500
#define ALICE 0
#define BOB 1

static int N, M, A[MAX_N*(MAX_N-1)/2], B[MAX_N*(MAX_N-1)/2];
static int V, U, C[MAX_V*(MAX_V-1)/2], D[MAX_V*(MAX_V-1)/2];
static int C_[MAX_V*(MAX_V-1)/2], D_[MAX_V*(MAX_V-1)/2];
static int N_, M_, A_[MAX_V*(MAX_V-1)/2], B_[MAX_V*(MAX_V-1)/2];
static int max_dif = 0;

void Alice( int N, int M, int A[], int B[] );
void Bob( int V, int U, int C[], int D[] );

bool used[MAX_V*(MAX_V-1)/2];
bool exist_edge[MAX_N][MAX_N];
bool used_edge[MAX_N][MAX_N];
int cnt_makemap;
void init(){
	V = 0;
	U = 0;
	N_ = 0;
	for(int i = 0 ; i < MAX_V*(MAX_V-1)/2 ; i ++){
		used[i] = false;
	}
	for(int i = 0 ; i < MAX_N ; i ++){
		for(int j = 0 ; j < MAX_N ; j ++){
			exist_edge[i][j] = false;
			used_edge[i][j] = false;
		}
	}
	cnt_makemap = 0;
}

void WrongAnswer( int e ){
  fprintf( stderr, "Wrong Answer [%d]\n", e );
  exit( 0 );
}

void input_check( int e , int WA_num ){
  if( e == -1 ){
    WrongAnswer( WA_num );
  }
}

void InitG( int in_V, int in_U ){
	if(V != 0)WrongAnswer(6);
	if(in_V <= 0)WrongAnswer(1);
	if(in_V > MAX_V)WrongAnswer(1);
	V = in_V;
	if(in_U < 0)WrongAnswer(2);
	if(in_U > V*(V-1)/2)WrongAnswer(2);
	U = in_U;
}

void MakeG( int pos, int in_C, int in_D ){
	if(V == 0)WrongAnswer(7);
	if(pos < 0)WrongAnswer(3);
	if(pos >= U)WrongAnswer(3);
	if(used[pos])WrongAnswer(4);
	used[pos] = true;
	if(in_C < 0)WrongAnswer(5);
	if(in_C >= V)WrongAnswer(5);
	if(in_D < 0)WrongAnswer(5);
	if(in_D >= V)WrongAnswer(5);
	if(in_C == in_D)WrongAnswer(5);
	C[pos] = in_C;
	D[pos] = in_D;
}

void InitMap( int in_N, int in_M ){
	if(N_ != 0)WrongAnswer(15);
	N_ = in_N;
	if(N_ != N)WrongAnswer(10);
	M_ = in_M;
	if(M_ != M)WrongAnswer(11);
}

void shuffle(){
	std::random_device rnd;
	std::mt19937 mt(rnd());
	static pair<int,int> p[MAX_V];
	for(int i = 0 ; i < V ; i ++){
		p[i] = pair<int,int>( mt() , i );
	}
	sort(p,p+V);
	static pair<int,int> q[MAX_V*(MAX_V-1)/2];
	for(int i = 0 ; i < U ; i ++){
		q[i] = pair<int,int>( mt() , i );
	}
	sort(q,q+U);
	for(int i = 0 ; i < U ; i ++){
		C_[i] = p[C[q[i].second]].second;
		D_[i] = p[D[q[i].second]].second;
	}
	for(int i = 0 ; i < U ; i ++){
		C[i] = C_[i];
		D[i] = D_[i];
	}
}

void MakeMap( int in_A, int in_B ){
	if(N_ == 0)WrongAnswer(16);
	if(in_A < 0)WrongAnswer(12);
	if(in_A >= N)WrongAnswer(12);
	if(in_B < 0)WrongAnswer(12);
	if(in_B >= N)WrongAnswer(12);
	if(in_A == in_B)WrongAnswer(12);
	if(in_A > in_B)swap(in_A,in_B);
	if(!exist_edge[in_A][in_B])WrongAnswer(13);
	if(used_edge[in_A][in_B])WrongAnswer(14);
	used_edge[in_A][in_B] = true;
	cnt_makemap ++;
}

int main( int argc, char** argv ){
	init();

	scanf("%d%d",&N,&M);
	for(int i = 0 ; i < M ; i ++){
		scanf("%d%d",&A[i],&B[i]);
	}
	
	Alice( N, M, A, B );
	if(V == 0)WrongAnswer(8);
	for(int i = 0 ; i < U ; i ++){
		if(!used[i])WrongAnswer(8);
	}
	static bool edge_used[MAX_V][MAX_V];
	for(int i = 0 ; i < MAX_V ; i ++){
		for(int j = 0 ; j < MAX_V ; j ++){
			edge_used[i][j] = false;
		}
	}
	
	shuffle();
	
	for(int i = 0 ; i < U ; i ++){
		if(edge_used[C[i]][D[i]])WrongAnswer(9);
		edge_used[C[i]][D[i]] = true;
		edge_used[D[i]][C[i]] = true;
	}
	
	for(int i = 0 ; i < M ; i ++){
		exist_edge[A[i]][B[i]] = true;
		exist_edge[B[i]][A[i]] = true;
	}
	Bob( V, U, C, D );
	if(cnt_makemap != M)WrongAnswer(17);

  fprintf( stderr, "Accepted\n" );
  fprintf( stderr, "V = %d\n", V );
}
