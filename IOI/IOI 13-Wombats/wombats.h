#ifndef __WOMBATS_H__
#define __WOMBATS_H__

#ifdef __cplusplus
extern "C" {
#endif

void init(int R, int C, int H[5000][200], int V[5000][200]);
void changeH(int P, int Q, int W);
void changeV(int P, int Q, int W);
int escape(int V1, int V2);

#ifdef __cplusplus
}
#endif

#endif /* __WOMBATS_H__ */

