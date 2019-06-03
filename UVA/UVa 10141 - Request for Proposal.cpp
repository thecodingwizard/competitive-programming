#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <string>
#define INF 1000000000

using namespace std;

int main() {
    int n, p, metRequirements, rfpCount = 0, optimalCompliance = 0;
    float price, optimalCost = INF;
    string requirement, proposal, optimalProposal;

    while (cin >> n >> p, (n || p)) {
        if (rfpCount != 0) cout << endl;
        rfpCount++;
        cin.ignore();
        // read in requirements
        for (int i = 0; i < n; i++) {
            getline(cin, requirement); // requirement is actually not needed
        }

        // read in proposals
        for (int i = 0; i < p; i++) {
            getline(cin, proposal);
            cin >> price >> metRequirements;
            cin.ignore();
            for (int j = 0; j < metRequirements; j++) getline(cin, requirement); // requirement actually not needed
            if (metRequirements > optimalCompliance) {
                optimalCompliance = metRequirements;
                optimalProposal = proposal;
                optimalCost = price;
            } else if (metRequirements == optimalCompliance && optimalCost > price) {
                optimalProposal = proposal;
                optimalCost = price;
            }
        }

        cout << "RFP #" << rfpCount << endl;
        cout << optimalProposal << endl;
        optimalCost = INF;
        optimalCompliance = -1;
    }
    return 0;
}