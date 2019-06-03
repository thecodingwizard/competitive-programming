#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include <algorithm>
#include <stack>
#include <vector>

#define INF 1000000000

using namespace std;

string source, target;

void dfs(stack<char>& storage, string& tmp, int sourceIndex, vector<char>& moves) {
    if (target.find(tmp) != 0) {
        return;
    }

    if (target == tmp) {
        bool first = true;
        for (char move : moves) {
            if (first) {
                first = false;
            } else {
                cout << " ";
            }
            cout << move;
        }
        cout << endl;
        return;
    }

    if (sourceIndex < source.length()) {
        storage.push(source[sourceIndex++]);
        moves.push_back('i');
        dfs(storage, tmp, sourceIndex, moves);
        storage.pop();
        moves.pop_back();
        sourceIndex--;
    }

    if (!storage.empty()) {
        char removed = storage.top();
        tmp += removed;
        storage.pop();
        moves.push_back('o');
        dfs(storage, tmp, sourceIndex, moves);
        moves.pop_back();
        storage.push(removed);
        tmp = tmp.substr(0, tmp.length() - 1);
    }
}

int main() {

    while (cin >> source) {
        cin >> target;
        stack<char> storage;
        string tmp;
        vector<char> moves;
        cout << "[" << endl;
        dfs(storage, tmp, 0, moves);
        cout << "]" << endl;
    }

    return 0;
}