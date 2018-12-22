#include <iostream>
#include <map>
#include <queue>

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

int main() {
    int ans = 0;
    for (int x = 0; x <= target_x; ++x) {
        for (int y = 0; y <= target_y; ++y) {
            long long level = erosion_level(x, y) % 3;
            ans += level;
        }
    }
    cout << ans << endl;
}
