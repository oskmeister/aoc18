#include <iostream>
#include <map>
#include <set>

using namespace std;

const int depth = 3558;
const int target_x = 15;
const int target_y = 740;

const int MOD = 20183;

map<pair<int,int>, long long> cache;

long long geologic_index(int x, int y) {
    if (x == 0 && y == 0) return 0;
    if (x == target_x && y == target_y) return 0;
    if (y == 0) return (x * 16807) % MOD;
    if (x == 0) return (y * 48271) % MOD;
    if (cache.count(make_pair(x,y))) {
        return cache[make_pair(x,y)];
    }
    long long ret1 = (geologic_index(x-1, y) + depth) % MOD;
    long long ret2 = (geologic_index(x, y-1) + depth) % MOD;
    long long ans = (ret1 * ret2) % MOD;
    cache[make_pair(x,y)] = ans;
    return ans;
}

long long erosion_level(int x, int y) {
    return (geologic_index(x,y) + depth) % MOD;
}

struct State {
    int x;
    int y;
    int tool;
    const bool operator<(const State &other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return tool < other.tool;
    }
};

int main() {
    set<pair<int, State>> q;
    map<State, int> dist;

    const State first_state = {0, 0, 1};
    dist[first_state] = 0;
    q.insert(make_pair(0, first_state));
    while (!q.empty()) {
        auto cur = *q.begin();
        q.erase(q.begin());
        if (cur.second.x == target_x && cur.second.y == target_y) {
            cout << cur.first << endl;
            return 0;
        }
        const static int dx[4] = {0, -1, 0, 1};
        const static int dy[4] = {-1, 0, 1, 0};
        for (int i = 0; i < 4; ++i) {
            for (int t = 0; t < 3; ++t) {
                int nx = cur.second.x + dx[i];
                int ny = cur.second.y + dy[i];
                if (ny < 0 || nx < 0) continue;
                int tool_banned = erosion_level(nx, ny) % 3;
                if (tool_banned == t) continue;
                int tool_banned_current = erosion_level(cur.second.x, cur.second.y) % 3;
                if (tool_banned_current == t) continue;
                if (nx == target_x && ny == target_y && t != 1) continue;
                int next_dist = cur.first + 1 + (t != cur.second.tool ? 7 : 0);
                State next_state = {nx, ny, t};
                auto it = dist.find(next_state);
                if (it != dist.end()) {
                    if (it->second > next_dist) {
                        auto it2 = q.find(make_pair(it->second, next_state));
                        if (it2 != q.end()) {
                            q.erase(it2);
                        }
                        q.insert(make_pair(next_dist, next_state));
                        dist[next_state] = next_dist;
                    }
                } else {
                    q.insert(make_pair(next_dist, next_state));
                    dist[next_state] = next_dist;
                }
            }
        }
    }
}
