#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <utility>

using namespace std;

struct Unit {
    int type;
    int hp;
    int r,c;
};

struct State {
    vector<vector<Unit *>> units;
    vector<string> grid;
};

int to_type(char c) {
    return c == 'G';
}

const static int dr[4] = { -1, 0, 0, 1 };
const static int dc[4] = { 0, -1, 1, 0 };

vector<pair<int,int>> find_candidates(int type, State &state) {
    vector<pair<int,int>> result;
    auto &grid = state.grid;
    auto &units = state.units;
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            if (units[r][c] && units[r][c]->type == type) {
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[0].size() && grid[nr][nc] == '.' && !state.units[nr][nc]) {
                        result.push_back(make_pair(nr,nc));
                    }
                }
            }
        }
    }
    return result;
}

pair<int,int> get_move(vector<pair<int,int>> candidates, State &state, int at_r, int at_c) {
    auto &grid = state.grid;
    auto &units = state.units;
    const int inf = 1<<30;
    vector<vector<int>> dist(grid.size(), vector<int>(grid[0].size(), inf));
    vector<vector<pair<int,int>>> path(grid.size(), vector<pair<int,int>>(grid[0].size()));
    queue<pair<int,int>> q;
    q.push({at_r, at_c});
    dist[at_r][at_c] = 0;
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        int cr = cur.first;
        int cc = cur.second;
        for (int d = 0; d < 4; ++d) {
            int nr = cr + dr[d];
            int nc = cc + dc[d];
            if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[0].size() && grid[nr][nc] == '.' && !units[nr][nc] && dist[nr][nc] == inf) {
                dist[nr][nc] = dist[cr][cc] + 1;
                path[nr][nc] = make_pair(cr, cc);
                q.push({nr, nc});
            }
        }
    }

    int best = inf;
    pair<int,int> bestpoint;
    for (auto x : candidates) {
        int r = x.first;
        int c = x.second;
        if (dist[r][c] < best) {
            best = dist[r][c];
            bestpoint = x;
        }
    }
    if (best == inf) {
        return {0, 0};
    }

    // Backtrack
    auto p = bestpoint;
    for (;;) {
        if (path[p.first][p.second] == make_pair(at_r, at_c)) {
            return p;
        }
        p = path[p.first][p.second];
    }

    return {0, 0};
}

vector<Unit *> find_stuff_to_hit(State &state, int r, int c, int target) {
    auto &grid = state.grid;
    auto &units = state.units;
    vector<Unit *> ret;
    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[0].size() && units[nr][nc] && units[nr][nc]->type == target) {
            ret.push_back(units[nr][nc]);
        }
    }
    return ret;
}

bool act(State &state, int r, int c, int attack_power) {
    auto &grid = state.grid;
    auto &units = state.units;
    int target = (units[r][c]->type) ^ 1;

    bool found = false;
    for (int rr = 0; rr < grid.size(); ++rr) {
        for (int cc = 0; cc < grid.size(); ++cc) {
            if (units[rr][cc] && units[rr][cc]->type == target) found = true;
        }
    }
    if (!found) return false;

    auto cand = find_candidates(target, state);
    auto move = get_move(cand, state, r, c);
    vector<Unit *> enemies_nearby_pre = find_stuff_to_hit(state, r, c, target);
    if (move != make_pair(0,0) && enemies_nearby_pre.empty()) {
        int nr = move.first;
        int nc = move.second;
        swap(grid[nr][nc], grid[r][c]);
        swap(units[nr][nc], units[r][c]);
        units[nr][nc]->r = nr;
        units[nr][nc]->c = nc;
        r = nr;
        c = nc;
    }
    if (enemies_nearby_pre.empty() && move == make_pair(0, 0)) {
        // No move.
        return true;
    }
    vector<Unit *> enemies_nearby = find_stuff_to_hit(state, r, c, target);
    if (!enemies_nearby.empty()) {
        int least_hp = 1<<30;
        Unit *best = NULL;
        for (Unit *u : enemies_nearby) {
            if (u->hp < least_hp) {
                least_hp = u->hp;
                best = u;
            }
        }
        int dmg = target == 1 ? attack_power : 3;
        best->hp -= dmg;
        if (best->hp <= 0) {
            // Die!
            units[best->r][best->c] = NULL;
        }
    }
    return true;
}

bool simulate_round(State &state, int dmg) {
    auto &grid = state.grid;
    auto &units = state.units;

    vector<Unit *> units_to_move;
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            if (units[r][c]) {
                units_to_move.push_back(units[r][c]);
            }
        }
    }
    for (Unit *u : units_to_move) {
        if (u->hp <= 0) continue;
        int r = u->r;
        int c = u->c;
        if (!act(state, r, c, dmg)) return false;
    }
    return true;
}

bool elves_won(vector<string> input, int dmg) {
    State s;
    {
        string str;
        for (int i = 0; i < input.size(); ++i) {
            s.grid.push_back(input[i]);
        }
    }

    s.units.resize(s.grid.size());
    for (int i = 0; i < s.grid.size(); ++i) {
        s.units[i].resize(s.grid[0].size());
    }

    int num_elves = 0;
    for (int i = 0; i < s.grid.size(); ++i) {
        for (int j = 0; j < s.grid[0].size(); ++j) {
            if (s.grid[i][j] == 'E') {
                ++num_elves;
                auto unit = new Unit();
                unit->type = 0;
                unit->hp = 200;
                unit->r = i;
                unit->c = j;
                s.units[i][j] = unit;
                s.grid[i][j] = '.';
            } else if (s.grid[i][j] == 'G') {
                auto unit = new Unit();
                unit->type = 1;
                unit->hp = 200;
                unit->r = i;
                unit->c = j;
                s.units[i][j] = unit;
                s.grid[i][j] = '.';
            } else {
                s.units[i][j] = NULL;
            }
        }
    }

    int rounds = 0;
    for (;;) {
        bool ok = simulate_round(s, dmg);
        if (!ok) break;
        ++rounds;
    }
    int sumhp = 0;
    int check_num_elves = 0;
    for (int r = 0; r < s.grid.size(); ++r) {
        for (int c = 0; c < s.grid[0].size(); ++c) {
            if (s.units[r][c]) {
                if (s.units[r][c]->type == 0) ++check_num_elves;
                sumhp += s.units[r][c]->hp;
            }
        }
    }

    if (num_elves != check_num_elves) return false;

    cout << "Answer: " << sumhp * rounds << endl;
    return true;
}

int main() {
    vector<string> input;
    string str;
    while (cin >> str) {
        input.push_back(str);
    }
    int dmg = 14;
    while (!elves_won(input, dmg++));
}
