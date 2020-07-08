/*
 * note that v will be very small. The vast, vast majority of the prizes
 * are all going to be of type v. The solution below aims to binary search
 * on prizes with type v, and manually check every prize that's not type v.
 *
 * The function solve(l, r, numLeft, numRight) will check all prizes in [l, r]
 * assuming there are `numLeft` prizes < v to the left of l and `numRight` prizes < v
 * to the right of r.
 *
 * We can prune this: if numLeft + numRight = numPrizesLessThanV, then we can
 * immediately exit; everything in [l, r] is of type v.
 *
 * Then, we check (l+r)/2. If it is a prize of type v, then our binary
 * serach can recurse. If it is not, then we check to see if it is a diamond
 * and pick another point close to the middle.
 *
 * As we are only checking each non-type-v prize once, and there aren't
 * that many of them, this will run within 5000 queries (idk how to prove oops).
 *
 * However, we need to determine what is "type v," we can do this by querying
 * 500 prizes and noting down the largest ask(i)[0] + ask(i)[1], but this
 * uses too many queries.
 *
 * Instead, we can do something really dumb (not sure why this works either oops)
 * and just update `biggestCt` in the solve() function. This will
 * screw up `numLeft` and `numRight` which may result in more queries, but it
 * receives AC anyway (probably because `numLeft` and `numRight` will be
 * quickly updated to the right values)
 */

#include "prize.h"

using namespace std;

#define vi vector<int>

int biggestCt = -1;

int solve(int l, int r, int numLeft, int numRight) {
    if (l > r) return -1;

    if (numLeft + numRight == biggestCt) return -1;
    for (int mid = (l+r)/2; mid <= r; mid++) {
        vi res = ask(mid);
        int sum = res[0] + res[1];
        if (sum == 0) return mid;
        if (sum > biggestCt) {
            biggestCt = sum;
        }
        if (sum != biggestCt) continue;
        int ans = solve(mid+1, r, res[0], numRight);
        if (ans != -1) return ans;
        return solve(l, (l+r)/2-1, numLeft, res[1] + mid-(l+r)/2);
    }
    for (int mid = (l+r)/2-1; mid >= l; mid--) {
        vi res = ask(mid);
        int sum = res[0] + res[1];
        if (sum == 0) return mid;
        if (sum > biggestCt) {
            biggestCt = sum;
        }
        if (sum != biggestCt) continue;
        int ans = solve(l, mid-1, numLeft, res[1]);
        if (ans != -1) return ans;
        break;
    }
	return -1;
}

int find_best(int n) {
    return solve(0, n-1, 0, 0);
}
