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

using namespace std;

#define INF 1000000000
#define LSOne(S) (S & (-S))
#define EPS 1e-9
typedef vector<int> vi;

char format;
int rows, cols;
int bitmap[201][201];
int charCount = 0;

bool same(int startx, int starty, int endx, int endy) {
    int val = -1;
    for (int i = startx; i < endx; i++) {
        for (int j = starty; j < endy; j++) {
            if (val == -1) val = bitmap[i][j];
            if (val != bitmap[i][j]) return false;
        }
    }
    return true;
}

void printBitmap(int startx, int starty, int endx, int endy) {
    if (startx >= endx || starty >= endy) return;
    if (same(startx, starty, endx, endy)) {
        cout << bitmap[startx][starty];
        charCount++;
        if (charCount == 50) {
            cout << endl;
            charCount = 0;
        }
    } else {
        cout << "D";
        charCount++;
        if (charCount == 50) {
            cout << endl;
            charCount = 0;
        }
        printBitmap(startx, starty, startx+(endx-startx+1)/2, starty+(endy-starty+1)/2);
        printBitmap(startx, starty+(endy-starty+1)/2, startx+(endx-startx+1)/2, endy);
        printBitmap(startx+(endx-startx+1)/2, starty, endx, starty+(endy-starty+1)/2);
        printBitmap(startx+(endx-startx+1)/2, starty+(endy-starty+1)/2, endx, endy);
    }
}

void constructBitmap(int startx, int starty, int endx, int endy) {
    if (startx >= endx || starty >= endy) return;
    char c;
    cin >> c;
    if (c == 'D') {
        constructBitmap(startx, starty, startx+(endx-startx+1)/2, starty+(endy-starty+1)/2);
        constructBitmap(startx, starty+(endy-starty+1)/2, startx+(endx-startx+1)/2, endy);
        constructBitmap(startx+(endx-startx+1)/2, starty, endx, starty+(endy-starty+1)/2);
        constructBitmap(startx+(endx-startx+1)/2, starty+(endy-starty+1)/2, endx, endy);
    } else {
        for (int i = startx; i < endx; i++) {
            for (int j = starty; j < endy; j++) {
                bitmap[i][j] = c - '0';
            }
        }
    }
}

int main() {
    while (cin >> format >> rows >> cols) {
        charCount = 0;
        if (format == 'B') {
            string s;
            int x = 0, r = 0, c = 0;
            while (x < rows * cols) {
                cin >> s;
                for (char i : s) {
                    bitmap[r][c++] = i - '0';
                    if (c >= cols) {
                        c = 0;
                        r++;
                    }
                    x++;
                }
            }
            cout << "D" << setw(4) << rows << setw(4) << cols << endl;
            printBitmap(0, 0, rows, cols);
            cout << endl;
        } else {
            cout << "B" << setw(4) << rows << setw(4) << cols << endl;
            constructBitmap(0, 0, rows, cols);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << bitmap[i][j];
                    charCount++;
                    if (charCount == 50 && !(i == rows - 1 && j == cols - 1)) {
                        cout << endl;
                        charCount = 0;
                    }
                }
            }
            cout << endl;
        }
    }
    return 0;
}