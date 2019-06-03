#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>

#define INF 1000000000

using namespace std;

struct Contestant {
    int id;
    int numSolved;
    int time;
    bool solved[10];
    int attempts[10];
    bool active;
};

bool sortByNumSolved(Contestant a, Contestant b) {
    if (a.numSolved > b.numSolved) return true;
    if (b.numSolved > a.numSolved) return false;

    if (a.time > b.time) return false;
    if (b.time > a.time) return true;

    return a.id < b.id;
}

int N, n;

int main() {
    cin >> N;
    cin.ignore();

    int contestant, problem, time;
    char result;
    string str;
    stringstream ss;
    getline(cin, str);
    Contestant data[101];

    for (int i = 0; i < N; i++) {
        if (i != 0) {
            cout << endl;
        }

        for (int j = 0; j < 101; j++) {
            data[j].id = j;
            data[j].active = false;
            data[j].numSolved = 0;
            data[j].time = 0;
            for (int k = 0; k < 10; k++) {
                data[j].solved[k] = false;
                data[j].attempts[k] = 0;
            }
        }

        while (getline(cin, str)) {
            if (str.empty()) break;

            ss << str;
            ss >> contestant >> problem >> time >> result;

            data[contestant].active = true;
            if (data[contestant].solved[problem]) continue;

            if (result == 'C') {
                data[contestant].time += time + 20 * data[contestant].attempts[problem];
                data[contestant].numSolved++;
                data[contestant].solved[problem] = true;
            } else if (result == 'I') {
                data[contestant].attempts[problem]++;
            }
        }

        sort(begin(data), end(data), sortByNumSolved);

        for (auto& contestant : data) {
            if (contestant.active) {
                cout << contestant.id << " " << contestant.numSolved << " " << contestant.time << endl;
            }
        }
    }

    return 0;
}