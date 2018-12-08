#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

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
    string input;
    cin >> input;
    for (;;) {
        string after = process(input);
        if (after == input) break;
        input = after;
    }
    cout << input.size() << endl;
}

