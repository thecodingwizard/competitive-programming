#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <string>
#define INF 1000000000

using namespace std;

const char Club = 'C';
const char Diamond = 'D';
const char Heart = 'H';
const char Spade = 'S';

struct Card {
    char suit;
    int val;
};

int main() {
    string tmp;
    Card cards[13];
    char suit, charVal;
    int val;
    while (true) {
        for (auto &card : cards) {
            cin >> tmp;
            if (tmp.empty()) goto end;

            charVal = tmp[0];
            suit = tmp[1];
            if (charVal == 'K') val = 13;
            else if (charVal == 'Q') val = 12;
            else if (charVal == 'J') val = 11;
            else if (charVal == 'T') val = 10;
            else if (charVal == 'A') val = 14;
            else val = charVal - '0';

            card.suit = suit;
            card.val = val;
        }

        int score = 0, club = 0, heart = 0, diamond = 0, spade = 0;
        bool clubStop = false, heartStop = false, diamondStop = false, spadeStop = false;
        for (auto &card : cards) {
            if (card.val == 14) score += 4;
            else if (card.val == 13) score += 3;
            else if (card.val == 12) score += 2;
            else if (card.val == 11) score += 1;

            if (card.suit == Club) club++;
            else if (card.suit == Heart) heart++;
            else if (card.suit == Diamond) diamond++;
            else if (card.suit == Spade) spade++;
        }

        for (auto &card : cards) {
            if (card.val == 13) {
                if (card.suit == Club && club == 1) score--;
                else if (card.suit == Heart && heart == 1) score--;
                else if (card.suit == Diamond && diamond == 1) score--;
                else if (card.suit == Spade && spade == 1) score--;
            } else if (card.val == 12) {
                if (card.suit == Club && club <= 2) score--;
                else if (card.suit == Heart && heart <= 2) score--;
                else if (card.suit == Diamond && diamond <= 2) score--;
                else if (card.suit == Spade && spade <= 2) score--;
            } else if (card.val == 11) {
                if (card.suit == Club && club <= 3) score--;
                else if (card.suit == Heart && heart <= 3) score--;
                else if (card.suit == Diamond && diamond <= 3) score--;
                else if (card.suit == Spade && spade <= 3) score--;
            }

            if (card.val == 14) {
                if (card.suit == Club) clubStop = true;
                else if (card.suit == Diamond) diamondStop = true;
                else if (card.suit == Heart) heartStop = true;
                else if (card.suit == Spade) spadeStop = true;
            } else if (card.val == 13) {
                if (card.suit == Club && club >= 2) clubStop = true;
                else if (card.suit == Diamond && diamond >= 2) diamondStop = true;
                else if (card.suit == Heart && heart >= 2) heartStop = true;
                else if (card.suit == Spade && spade >= 2) spadeStop = true;
            } else if (card.val == 12) {
                if (card.suit == Club && club >= 3) clubStop = true;
                else if (card.suit == Diamond && diamond >= 3) diamondStop = true;
                else if (card.suit == Heart && heart >= 3) heartStop = true;
                else if (card.suit == Spade && spade >= 3) spadeStop = true;
            }
        }

        if (clubStop && diamondStop && heartStop && spadeStop && score >= 16) {
            cout << "BID NO-TRUMP" << endl;
            tmp = "";
            continue;
        }

        if (club == 2) score += 1;
        if (diamond == 2) score += 1;
        if (heart == 2) score += 1;
        if (spade == 2) score += 1;

        if (club == 1 || club == 0) score += 2;
        if (diamond == 1 || diamond == 0) score += 2;
        if (heart == 1 || heart == 0) score += 2;
        if (spade == 1 || spade == 0) score += 2;

        char bid = 'S';
        int bidLength = spade;

        if (heart > bidLength) {
            bid = 'H';
            bidLength = heart;
        }
        if (diamond > bidLength) {
            bid = 'D';
            bidLength = diamond;
        }
        if (club > bidLength) {
            bid = 'C';
            bidLength = club;
        }

        if (score < 14) {
            cout << "PASS" << endl;
        } else {
            cout << "BID " << bid << endl;
        }
        tmp = "";
    }

    end:
    return 0;
}