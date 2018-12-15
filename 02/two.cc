#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> v;
    string str;
    while (cin >> str) {
        v.push_back(str);
    }

    for (int i = 0; i < v.size(); ++i) {
        for (int j = i+1; j < v.size(); ++j) {
            int diff = 0;
            for (int k = 0; k < v[i].size(); ++k) {
                if (v[i][k] != v[j][k]) {
                    ++diff;
                }
            }
            if (diff == 1) {
                cout << v[i] << endl;
                cout << v[j] << endl;
            }
        }
    }
}
