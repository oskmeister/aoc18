#include <vector>
#include <iostream>

using namespace std;

int grid[1000][1000];

int main() {
    int r, c, h, w;
    while (cin >> r >> c >> h >> w) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                grid[r+i][c+j]++;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            ans += grid[i][j] >= 2;
        }
    }
    cout << ans << endl;
}
