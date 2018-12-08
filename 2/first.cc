#include <iostream>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

int main() {
    int two = 0;
    int three = 0;
    string input;
    while (cin >> input) {
        set<char> s(input.begin(), input.end());
        for (char c : s) {
            if (count(input.begin(), input.end(), c) == 2) {
                two++;
                break;
            }
        }
        for (char c : s) {
            if (count(input.begin(), input.end(), c) == 3) {
                three++;
                break;
            }
        }
    }
    cout << two * three << endl;
}
