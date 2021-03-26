/*
 * My solution is quite bad, use the editorial solution instead
 *
 * I communicated how many times each number would be used before its removed by sending a bunch of 1's following by a zero
 *
 * Use the editorial solution
 */

#include <bits/stdc++.h>
#include "advisor.h"

using namespace std;

#define s second
#define f first

queue<int> nextUse[100000];

void ComputeAdvice(int *C, int N, int K, int M) {
    vector<int> uses(K, 0);
    for (int i = 0; i < N; i++) {
        //cout << "using " << C[i] << " at " << i << endl;
        nextUse[C[i]].push(i);
    }
    for (int i = 0; i < N; i++) {
        nextUse[i].push(N);
    }

    // first holds next use time, second holds k-index, third holds whether its among the first k
    set<pair<int, pair<int, int>>> stuff;
    set<int> inSet;
    map<int, int> pos;
    map<int, int> revPos;
    map<int, int> addedTime;
    for (int i = 0; i < K; i++) {
        //cout << "ADDING " << nextUse[i].front() << " " << i << " " << 1 << endl;
        stuff.insert(make_pair(nextUse[i].front(), make_pair(i, 1)));
        nextUse[i].pop();
        inSet.insert(i);
        pos[i] = i;
        revPos[i] = i;
        addedTime[i] = i;
    }

    int nextCt = 0;
    vector<int> count(N, 0);
    int timeCtr = K;
    for (int i = 0; i < N; i++) {
        //cout << "============ ";
        //for (int j = 0; j < K; j++) cout << revPos[j];
        //cout << " ============" << endl;
        int c = C[i];
        if (inSet.count(c)) {
            //cout << "used " << c << endl;
            uses[pos[c]]++;
            count[addedTime[pos[c]]]++;
        } else {
            while (stuff.begin()->f < i) {
                int c2 = revPos[stuff.begin()->s.f];
                while (!nextUse[c2].empty() && nextUse[c2].front() < i) nextUse[c2].pop();
                int nextTime = N;
                if (!nextUse[c2].empty()) {
                    nextTime = nextUse[c2].front(); nextUse[c2].pop();
                }
                pair<int, int> bkup = stuff.begin()->s;
                stuff.erase(stuff.begin());
                stuff.insert(make_pair(nextTime, bkup));
            }
            pair<int, pair<int, int>> toRemove = *stuff.rbegin();
            stuff.erase(--stuff.end());

            if (toRemove.s.s) {
                count[toRemove.s.f] = uses[toRemove.s.f];
            } else {
                assert(count[addedTime[toRemove.s.f]] == uses[toRemove.s.f]);
                count[addedTime[toRemove.s.f]] = uses[toRemove.s.f];
                nextCt++;
            }

            uses[toRemove.s.f] = 0;

            int removeColor = revPos[toRemove.s.f];
            //cout << "removing " << removeColor << " which is next used " << toRemove.f << endl;
            //cout << "and used " << c << endl;
            inSet.erase(removeColor);
            pos.erase(removeColor);

            revPos[toRemove.s.f] = c;
            inSet.insert(c);
            pos[c] = toRemove.s.f;
            int nextTime = N;
            if (!nextUse[c].empty()) {
                while (nextUse[c].front() <= i) nextUse[c].pop();
                nextTime = nextUse[c].front(); nextUse[c].pop();
            }
            stuff.insert(make_pair(nextTime, make_pair(toRemove.s.f, 0)));
            addedTime[toRemove.s.f] = timeCtr++;
        }
    }

    for (auto x : stuff) {
        if (x.s.s) count[x.s.f] = uses[x.s.f];
    }

    for (int i = 0; i < timeCtr; i++) {
        //cout << count[i] << " ";
        for (int j = 0; j < count[i]; j++) WriteAdvice(1);
        WriteAdvice(0);
    }
    //cout << nextCt << "-------------------------" << endl;
    //cout << endl;
}
