/*
 * See: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Info1Cup/2018%20-%20International%20Round/Info1Cup%2018-Hidden.cpp
 * And: https://github.com/tmwilliamlin168/CompetitiveProgramming/blob/master/Info1Cup/18-Hidden.cpp
 */

#include <bits/stdc++.h>
#include "grader.h"

using namespace std;

bool qry(int zeroes, int ones, bool rev = false) {
    vector<int> v;
    for (int i = 0; i < zeroes; i++) {
        v.push_back(0);
    }
    for (int j = 0; j < ones; j++) {
        v.push_back(1);
    }
    if (rev) reverse(v.begin(), v.end());
    return isSubsequence(v);
}

vector<int> findSequence (int N)
{
    int numZeroes = 1, numOnes = 1;
    for (; numZeroes <= N/2+1; numZeroes++) {
        if (qry(numZeroes, 0)) {
            continue;
        } else {
            break;
        }
    }
    numZeroes--;
    if (numZeroes == N/2+1) {
        for (; numOnes <= N/2+1; numOnes++) {
            if (qry(0, numOnes, true)) {
                continue;
            } else {
                break;
            }
        }
        numOnes--;
        numZeroes = N - numOnes;
    } else {
        numOnes = N - numZeroes;
    }

    vector<int> ans;
    int usedZeroes = 0;

    for (int i = 0; i < numOnes; i++) {
        int newZeroes = 0;
        for (int j = 1; j <= numZeroes - usedZeroes; j++) {
            if (usedZeroes + j + numOnes - i <= N/2+1) {
                if (qry(usedZeroes + j, numOnes - i)) {
                    newZeroes++;
                } else {
                    break;
                }
            } else {
                if (qry(numZeroes - usedZeroes - j, i+1, true) && !qry(numZeroes - usedZeroes - (j-1), i+1, true)) {
                    newZeroes = j;
                } else {
                    continue;
                }
            }
        }
        for (int i = 0; i < newZeroes; i++) {
            ans.push_back(0);
        }
        ans.push_back(1);
        usedZeroes += newZeroes;
    }

    while ((int)ans.size() != N) {
        ans.push_back(0);
    }

    return ans;
}

