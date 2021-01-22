/*
 * If we're solving a permutation of length n, we'll add n/2 elements to determine
 * where the n/2 right elements go. For example, if n = 4, we send:
 *
 * 0001
 * 0010
 *
 * Then, by checking 0001/0010/0100/1000 we can determine where the left two indices
 * go and where the right two indices go.
 *
 * Now we've reduced this to two subproblems of size n/2. We'll use the same logic
 * for n/2, and we'll fill in the remaining indices with 1's.
 *
 * So for n = 4, we'll add the following elements:
 *
 * (Solving n=4)
 * 0001
 * 0010
 *
 * (Solving n=2 for the right)
 * 1101
 * 1110
 *
 * (Solving n=2 for the left)
 * 0111
 * 1011
 *
 * See implementation below
 */

#include <bits/stdc++.h>
#include "messy.h"

using namespace std;

void addStuff(int n, string pref, string suff) {
    if (n == 1) return;
    for (int i = n/2; i < n; i++) {
        string s;
        for (int j = 0; j < n; j++) {
            if (j == i) s += "1";
            else s += "0";
        }
        add_element(pref + s + suff);
    }
    string halfZeroes; for (int i = 0; i < n/2; i++) halfZeroes += "1";
    addStuff(n/2, pref+halfZeroes, suff);
    addStuff(n/2, pref, halfZeroes+suff);
}

void checkStuff(vector<int> &perm, int n, vector<int> indices, int lo, int hi) {
    if (indices.size() == 1) {
        perm[indices[0]] = lo;
        return;
    }
    string s; for (int i = 0; i < n; i++) s += "1";
    for (auto x : indices) s[x] = '0';
    
    vector<int> leftHalf;
    vector<int> rightHalf;
    for (auto x : indices) {
        s[x] = '1';
        if (check_element(s)) {
            rightHalf.push_back(x);
        } else {
            leftHalf.push_back(x);
        }
        s[x] = '0';
    }

    checkStuff(perm, n, leftHalf, lo, (lo+hi)/2);
    checkStuff(perm, n, rightHalf, (lo+hi)/2+1, hi);
}

vector<int> restore_permutation(int n, int w, int r) {
    addStuff(n, "", "");
    compile_set();
    vector<int> perm(n);
    vector<int> indices(n); iota(indices.begin(), indices.end(), 0);

    checkStuff(perm, n, indices, 0, n-1);

    return perm;
}
