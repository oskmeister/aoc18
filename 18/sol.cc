#include <iostream>
#include <string>
#include <vector>


using namespace std;

vector<string> v;

void simulate() {
    vector<string> new_state = v;
    const int R = v.size();
    const int C = v[0].size();
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            int lumber = 0;
            int trees = 0;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr == 0 && dc == 0) continue;
                    int nr = r + dr;
                    int nc = c + dc;
                    if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                        if (v[nr][nc] == '|') trees++;
                        if (v[nr][nc] == '#') lumber++;
                    }
                }
            }
            if (v[r][c] == '.') {
                if (trees >= 3) new_state[r][c] = '|';
            }
            if (v[r][c] == '|') {
                if (lumber >= 3) new_state[r][c] = '#';
            }
            if (v[r][c] == '#') {
                if (lumber < 1 || trees < 1) new_state[r][c] = '.';
            }
            cout << new_state[r][c];
        }
        cout << endl;
    }
    cout << endl;
    v = new_state;
}

int main() {
    string str;
    while (cin >> str) {
        v.push_back(str);
    }

    for (int i = 0; i < 1000; ++i) {
        simulate();
    }

    int wood = 0;
    int lumber = 0;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[0].size(); ++j) {
            if (v[i][j] == '|') ++wood;
            if (v[i][j] == '#') ++lumber;
        }
    }

    cout << wood * lumber << endl;
}
