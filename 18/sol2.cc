#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>


using namespace std;

vector<string> v;
map<vector<string>, int> seen;
map<int, vector<string>> at;

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
        }
    }
    v = new_state;
}

int main() {
    string str;
    while (cin >> str) {
        v.push_back(str);
    }

    long long dist_to_cycle, cycle_len;
    for (int i = 0; i < 1000; ++i) {
        auto it = seen.find(v);
        if (it != seen.end()) {
            cycle_len = i - it->second;
            dist_to_cycle = it->second;
            break;
        }
        seen[v] = i;
        at[i] = v;
        simulate();
    }

    map<int, vector<string>> at2;
    for (auto p : at) {
        if (p.first >= dist_to_cycle) {
            at2[p.first-dist_to_cycle] = p.second;
        }
    }

    int wood = 0;
    int lumber = 0;

    vector<string> v_end = at2[(1000000000LL - dist_to_cycle) % at2.size()];

    for (int i = 0; i < v_end.size(); ++i) {
        for (int j = 0; j < v_end[0].size(); ++j) {
            if (v_end[i][j] == '|') ++wood;
            if (v_end[i][j] == '#') ++lumber;
        }
    }

    cout << wood * lumber << endl;
}
