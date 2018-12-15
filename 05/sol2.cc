#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string filter(const std::string &input, char c) {
    string str;
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == c || input[i] + 32 == c) {
            continue;
        }
        str.push_back(input[i]);
    }
    return str;
}

string process(const std::string &input) {
    string str;
    bool changed = false;
    for (int i = 0; i < input.size(); ++i) {
        char a = input[i];
        char b = input[i+1];
        if (abs(a-b) == 32) {
            ++i;
        } else {
            str.push_back(input[i]);
        }
    }

    return str;
}

int main() {
    int best = 1<<30;
    string input;
    cin >> input;
    for (char c = 'a'; c <= 'z'; ++c) {
        string input2 = filter(input, c);
        for (;;) {
            string after = process(input2);
            if (after == input2) break;
            input2 = after;
        }
        best = min(best, (int)input2.length());
    }
    cout << best << endl;
}

