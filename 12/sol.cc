#include <iostream>
#include <map>

using namespace std;

int main() {
    string str;
    cin >> str >> str >> str;


    string padding;
    for (int i = 0; i < 30; ++i) padding.push_back('.');
    string state = str;
    state = padding + state;
    state = state + padding;

    map<string,bool> m;
    while (cin >> str) {
        string val;
        cin >> val >> val;
        m[str] = val == "#";
    }

    for (int i = 0; i < state.size(); ++i) {
        cout << state[i];
    }
    cout << endl;
    for (int x = 0; x < 20; ++x) {
        string new_state(state.size(), '.');
        for (int i = 2; i < state.size() - 2; ++i) {
            const string s = state.substr(i-2, 5);
            if (m[s]) {
                new_state[i] = '#';
            } else {
                new_state[i] = '.';
            }
        }
        state = new_state;
        for (int i = 0; i < state.size(); ++i) {
            cout << state[i];
        }
        cout << endl;
    }

    int ans = 0;
    for (int i = 0; i < state.size(); ++i) {
        int actual_number = i - padding.size();
        if (state[i] == '#') ans += actual_number;
    }
    cout << ans << endl;
}
