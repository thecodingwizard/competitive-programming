#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'getRoundResult' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. CHARACTER winning_suit
 *  2. CHARACTER suit1
 *  3. INTEGER number1
 *  4. CHARACTER suit2
 *  5. INTEGER number2
 */

string getRoundResult(char winning_suit, char suit1, int number1, char suit2, int number2) {
    if (suit1 == winning_suit && suit2 != winning_suit) {
        return "Player 1 wins";
    }
    if (suit1 != winning_suit && suit2 == winning_suit) {
        return "Player 2 wins";
    }
    if (number1 == number2) {
        return "Draw";
    }
    if (number1 > number2) {
        return "Player 1 wins";
    } else {
        return "Player 2 wins";
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string winning_suit_temp;
    getline(cin, winning_suit_temp);

    char winning_suit = winning_suit_temp[0];

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    for (int n_itr = 0; n_itr < n; n_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        char suit1 = first_multiple_input[0][0];

        int number1 = stoi(first_multiple_input[1]);

        char suit2 = first_multiple_input[2][0];

        int number2 = stoi(first_multiple_input[3]);

        string result = getRoundResult(winning_suit, suit1, number1, suit2, number2);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
            s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
            find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
            s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
