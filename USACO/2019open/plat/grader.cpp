//
// Created by thecodingwizard on 3/31/2019.
//

#include "grader.h"

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

int getN() {
    return 5;
}

int getQ() {
    cerr << "should not be called" << endl;
    assert(false);
    return 0;
}

void setFarmLocation(int id, int x, int y) {
    cout << "setFarmLocation(" << id << ") = (" << x << ", " << y << ")" << endl;
}

void addBox(int x1, int y1, int x2, int y2) {
    cout << "addBox: (" << x1 << ", " << y1 << "); (" << x2 << ", " << y2 << ")." << endl;
}
