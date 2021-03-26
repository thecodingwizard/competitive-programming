#include <bits/stdc++.h>
#include "assistant.h"

using namespace std;

#define f first
#define s second

void Assist(unsigned char *A, int N, int K, int R) {
    map<int, int> useLeft;
    int idx = 0;
    map<int, int> pos;
    map<int, int> revPos;
    queue<int> toRemove;
    for (int i = 0; i < K; i++) {
        int ct = 0;
        while (A[idx] != 0) {
            ct++;
            idx++;
        }
        idx++;
        useLeft[i] = ct;
        //cout << i << " will be used " << ct << " times " << endl;
        if (ct == 0) {
            toRemove.push(i);
            //cout << "ADDING " << i << endl;
        }
        pos[i] = i;
        revPos[i] = i;
    }

    for (int i = 0; i < N; i++) {
        int req = GetRequest();
        if (pos.count(req)) {
            useLeft[pos[req]]--;
            if (useLeft[pos[req]] == 0) {
                toRemove.push(pos[req]);
            }
        } else {
            if (toRemove.empty()) {
                for (int i = 0; i < K; i++) {
                    cout << i << ": " << revPos[i] << " " << useLeft[i] << ", ";
                }
                cout << endl;
                assert(!toRemove.empty());
            }
            int remove = toRemove.front(); toRemove.pop();
            //cout <<"REMOVING " << revPos[remove] << endl;
            PutBack(revPos[remove]);
            pos.erase(revPos[remove]);
            revPos[remove] = req;
            pos[req] = remove;
            int ct = 0;
            if (idx == R) {
                //cout << "RIP" << endl;
                ct = 10000000;
            } else {
                while (A[idx] != 0) {
                    ct++;
                    idx++;
                }
                idx++;
            }
            useLeft[remove] = ct;
            if (ct == 0) {
                toRemove.push(remove);
                //cout << "ADDING " << revPos[remove] << " x" << ct << endl;
            }
        }
    }
}
