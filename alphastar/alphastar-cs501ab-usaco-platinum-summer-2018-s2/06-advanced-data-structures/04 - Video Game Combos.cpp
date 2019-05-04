/*
Video Game Combos
=================

Bessie is playing a video game! In the game, the three letters 'A', 'B',
and 'C' are the only valid buttons. Bessie may press the buttons in any
order she likes; however, there are only N distinct combos possible (1 <= N
<= 20). Combo i is represented as a string S_i which has a length between 1
and 15 and contains only the letters 'A', 'B', and 'C'.

Whenever Bessie presses a combination of letters that matches with a combo,
she gets one point for the combo. Combos may overlap with each other or
even finish at the same time! For example if N = 3 and the three possible
combos are "ABA", "CB", and "ABACB", and Bessie presses "ABACB", she will
end with 3 points. Bessie may score points for a single combo more than once.

Bessie of course wants to earn points as quickly as possible. If she
presses exactly K buttons (1 <= K <= 1,000), what is the maximum number of
points she can earn?

PROBLEM NAME: combos

INPUT FORMAT:

* Line 1: Two space-separated integers: N and K.

* Lines 2..N+1: Line i+1 contains only the string S_i, representing
        combo i.

SAMPLE INPUT:

3 7
ABA
CB
ABACB

OUTPUT FORMAT:

* Line 1: A single integer, the maximum number of points Bessie can
        obtain.

SAMPLE OUTPUT:

4

OUTPUT DETAILS:

The optimal sequence of buttons in this case is ABACBCB, which gives 4
points--1 from ABA, 1 from ABACB, and 2 from CB.
*/
#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <bitset>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <math.h>
#include <assert.h>

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
#define A first
#define B second
#define mp make_pair
#define PI acos(-1.0)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int main() {
    int n, k; cin >> n >> k;
    vector<string> combos; combos.resize(n);
    for (int i = 0; i < n; i++) cin >> combos[i];
    map<string, int> mapping; int numPrefixes = 0;
    string reverseMapping[1000];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < combos[i].length(); j++) {
            string substr = combos[i].substr(0, j+1);
            if (mapping.find(substr) == mapping.end()) {
                reverseMapping[numPrefixes] = substr;
                mapping.insert(mp(substr, numPrefixes++));
            }
        }
    }
    vector<vi> transitions; transitions.resize(numPrefixes);
    vector<int> val; val.assign(numPrefixes, 0);
    for (auto const &x : mapping) {
        string s = x.A;
        string appendA = s + 'A';
        string appendB = s + 'B';
        string appendC = s + 'C';

        for (int i = 0; i < appendA.length(); i++) {
            string substr = appendA.substr(i, appendA.length());
            if (mapping.find(substr) != mapping.end()) {
                transitions[x.B].push_back(mapping[substr]);
                break;
            }
        }
        for (int i = 0; i < appendB.length(); i++) {
            string substr = appendB.substr(i, appendB.length());
            if (mapping.find(substr) != mapping.end()) {
                transitions[x.B].push_back(mapping[substr]);
                break;
            }
        }
        for (int i = 0; i < appendC.length(); i++) {
            string substr = appendC.substr(i, appendC.length());
            if (mapping.find(substr) != mapping.end()) {
                transitions[x.B].push_back(mapping[substr]);
                break;
            }
        }

        for (auto const &combo : combos) {
            if (ends_with(s, combo)) val[x.B]++;
        }
    }
    int dp[numPrefixes][k];
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < n; i++) {
        string s = combos[i];
        if (s.length() == 1) {
            dp[mapping[s]][0] = 1;
        }
    }
    for (int i = 0; i < k - 1; i++) {
        for (int j = 0; j < numPrefixes; j++) {
            if (reverseMapping[j].length() > i + 1) continue;
            for (auto transition : transitions[j]) {
                dp[transition][i + 1] = max(dp[transition][i + 1], (i >= 0 ? dp[j][i] : 0) + val[transition]);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < numPrefixes; i++) {
        ans = max(ans, dp[i][k - 1]);
    }
    cout << ans << endl;
    return 0;
}
