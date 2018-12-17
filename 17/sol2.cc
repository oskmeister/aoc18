#include <iostream>
#include <cstdio>

using namespace std;

const int GRID_SIZE = 4000;

int miny = 1<<30;
int maxy = -(1<<30);

int grid[GRID_SIZE][GRID_SIZE];
int is_done[GRID_SIZE][GRID_SIZE];

bool water(int y, int x) {
    if (y > maxy) return true;
    grid[y][x] = 2;
    int ans = 0;
    bool done = false;
    if (grid[y+1][x] == 2 && is_done[y+1][x]) {
        done = true;
    } else {
        if (grid[y+1][x] == 0) {
            done = water(y+1, x);
        }
        if (!done) {
            bool done_l = false;
            bool done_r = false;
            if (grid[y][x-1] == 0) done_l |= water(y, x-1);
            if (grid[y][x+1] == 0) done_r |= water(y, x+1);
            if (done_l && !done_r) for (int cx = x;grid[y][cx] == 2;) is_done[y][cx++] = true;
            if (!done_l && done_r) for (int cx = x;grid[y][cx] == 2;) is_done[y][cx--] = true;
            done |= done_l || done_r;
        }
    }
    is_done[y][x] = done;
    return done;
}

int main() {
    char c1, c2;
    int l, r1, r2;
    while (scanf("%c=%d, %c=%d..%d\n", &c1, &l, &c2, &r1, &r2) == 5) {
        if (c1 == 'x') {
            for (int i = r1; i <= r2; ++i) {
                grid[i][l] = 1;
                miny=min(i,miny);
                maxy=max(i,maxy);
            }
        }
        else if (c1 == 'y') {
            for (int i = r1; i <= r2; ++i) {
                grid[l][i] = 1;
            }
            miny=min(l,miny);
            maxy=max(l,maxy);
        }
    }

    water(0, 500);

    int ans = 0;
    for (int y = miny; y <= maxy; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            if (grid[y][x] == 2 && !is_done[y][x]) ++ans;
        }
    }
    cout << ans << endl;
}
