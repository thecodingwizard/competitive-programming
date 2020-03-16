#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'getStrength' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING password
 *  2. INTEGER weight_a
 */

int getStrength(string password, int weight_a) {
    // Complete the function
    int ans = 0;
    for (char c : password) {
        ans += (weight_a + c-'a')%26;
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string password;
    getline(cin, password);

    string weight_a_temp;
    getline(cin, weight_a_temp);

    int weight_a = stoi(ltrim(rtrim(weight_a_temp)));

    int strength = getStrength(password, weight_a);

    fout << strength << "\n";

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
