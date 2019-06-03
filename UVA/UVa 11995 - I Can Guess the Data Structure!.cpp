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

#define INF 1000000000

using namespace std;

int main() {
    int n, a, b;
    while (cin >> n) {
        stack<int> s;
        queue<int> q;
        priority_queue<int> pq;
        bool s_works = true, q_works = true, pq_works = true;
        while (n--) {
            cin >> a >> b;
            if (a == 1) {
                if (s_works) s.push(b);
                if (q_works) q.push(b);
                if (pq_works) pq.push(b);
            } else if (a == 2) {
                if (s_works) {
                    if (s.empty()) {
                        s_works = false;
                    } else {
                        int s_res = s.top();
                        s.pop();
                        if (s_res != b) {
                            s_works = false;
                        }
                    }
                }

                if (q_works) {
                    if (q.empty()) {
                        q_works = false;
                    } else {
                        int q_res = q.front();
                        q.pop();
                        if (q_res != b) {
                            q_works = false;
                        }
                    }
                }

                if (pq_works) {
                    if (pq.empty()) {
                        pq_works = false;
                    } else {
                        int pq_res = pq.top();
                        pq.pop();
                        if (pq_res != b) {
                            pq_works = false;
                        }
                    }
                }
            }
        }
        if (s_works && q_works && pq_works || s_works && q_works || s_works && pq_works || q_works && pq_works) {
            cout << "not sure" << endl;
        } else if (!s_works && !q_works && !pq_works) {
            cout << "impossible" << endl;
        } else if (s_works) {
            cout << "stack" << endl;
        } else if (q_works) {
            cout << "queue" << endl;
        } else if (pq_works) {
            cout << "priority queue" << endl;
        }
    }
    return 0;
}