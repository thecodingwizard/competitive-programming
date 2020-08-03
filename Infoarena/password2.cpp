/*
 * Maintain a sorted list of letters; each letter appears once in the list.
 * A letter x comes before a letter y if the first instance of x in the password
 * is before the first instance of y in the password.
 *
 * Let's say y appears 5 times in total in the password. Letter x will
 * come before y in the list if "xyyyyy" is a valid subsequence of the password.
 *
 * To initialize this list, we loop through all the letters and insert it in
 * the right location in the list. We can binary search to determine what this location is
 *
 * Then, while the list is not empty:
 * - Take the first letter of the list and append it to our answer
 * - Remove the first letter from the list
 * - Binary search where to re-insert the letter into the list
 *
 * Also see: https://github.com/stefdasca/CompetitiveProgramming/blob/master/Infoarena/password2.cpp
 */

#include <bits/stdc++.h>

using namespace std;

int N, S; 

string gen(int i, int ct) {
    string s;
    for (int x = 0; x < ct; x++) {
        s += string(1, 'a'+i);
    }
    return s;
}

int ask(string s) {
    cout << s << endl;
    int x; cin >> x;
    if (x == N) {
        exit(0);
    }
    return x;
}

int main() {
    cin.tie(0); ios_base::sync_with_stdio(false);

    cin >> N >> S;

    int ct[S];
    for (int i = 0; i < S; i++) {
        ct[i] = ask(gen(i, N));
    }

    vector<int> letters;
    for (int i = 0; i < S; i++) {
        if (ct[i] == 0) continue;
        int lo = 0, hi = letters.size(), ans = letters.size();
        while (lo < hi) {
            int mid = (lo + hi)/2;
            string s = string(1, 'a'+i)+gen(letters[mid], ct[letters[mid]]);
            if (ask(s) == (int)s.size()) {
                ans = mid;
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        letters.insert(letters.begin()+ans, i);
    }

    string res = "";

    while (!letters.empty()) {
        int x = letters[0];
        letters.erase(letters.begin());
        ct[x]--;
        res += string(1, 'a'+x);
        if (ct[x] == 0) continue;

        int lo = 0, hi = letters.size(), ans = letters.size();
        while (lo < hi) {
            int mid = (lo + hi)/2;
            string s = res + string(1, 'a'+x)+gen(letters[mid], ct[letters[mid]]);
            if (ask(s) == (int)s.size()) {
                ans = mid;
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        letters.insert(letters.begin()+ans, x);
    }

    ask(res);

    return 0;
}
