#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

string regex;

const int SZ = 700;
char grid[SZ][SZ];

void go(int pos, int r, int c) {
    if (regex[pos] == ')' || regex[pos] == '|' || regex[pos] == '$') return;
    if (regex[pos] == '(') {
        int open = 0;
        int at = pos;
        for (;;) {
            if (open == 0 && at != pos) break;
            if (regex[at] == '(') ++open;
            if (regex[at] == ')') --open;
            if ((regex[at] == '(' || regex[at] == '|') && open == 1) {
                go(at+1, r, c);
            }
            ++at;
        }
        go(at, r, c);
    } else {
        const char ord = regex[pos];
        if (ord == 'N') {
            grid[r-1][c] = '.'; grid[r-2][c] = '.';
            go(pos+1, r-2, c);
        }
        if (ord == 'E') {
            grid[r][c+1] = '.'; grid[r][c+2] = '.';
            go(pos+1, r, c+2);
        }
        if (ord == 'S') {
            grid[r+1][c] = '.'; grid[r+2][c] = '.';
            go(pos+1, r+2, c);
        }
        if (ord == 'W') {
            grid[r][c-1] = '.'; grid[r][c-2] = '.';
            go(pos+1, r, c-2);
        }
    }
}

int main() {
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            grid[i][j] = '0';
        }
    }

    cin >> regex;
    const int start_r = SZ/2;
    const int start_c = SZ/2;
    go(1, start_r, start_c);

    queue<pair<int,int>> q;
    vector<vector<int>> dist(SZ, vector<int>(SZ, 1<<30));

    dist[start_r][start_c] = 0;
    q.push(make_pair(start_r, start_c));
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        static int dr[4] = {0, 1, 0, -1};
        static int dc[4] = {1, 0, -1, 0};
        for (int d = 0; d < 4; ++d) {
            int nr = cur.first + dr[d];
            int nc = cur.second + dc[d];
            if (grid[nr][nc] == '.' && dist[nr][nc] == 1<<30) {
                dist[nr][nc] = dist[cur.first][cur.second]+1;
                q.push(make_pair(nr, nc));
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            if (dist[i][j] != 1<<30 && (dist[i][j] % 2 == 0) && (dist[i][j] / 2 >= 1000)) {
                ++ans;
            }
        }
    }

    cout << ans << endl;
}
