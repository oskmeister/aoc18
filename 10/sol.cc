#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

struct Point {
    int r, c, dr, dc;
};

void advance(vector<Point> &v) {
    for (auto &p : v) {
        p.r += p.dr;
        p.c += p.dc;
    }
}

int main() {
    vector<Point> v;
    {
        int r, c, dr, dc;
        while (scanf("position=< %d,  %d> velocity=< %d,  %d>\n", &c, &r, &dc, &dr) == 4) {
            Point p;
            cout << r << endl;
            p.r=r; p.c=c; p.dr=dr; p.dc=dc;
            v.push_back(p);
        }
    }

    for (int i = 0; i < 50000; ++i) {
        vector<vector<char>> grid(200, vector<char>(200, '.'));
        int minr = 1<<30;
        int minc = 1<<30;
        for (auto p : v) {
            minr = min(minr, p.r);
            minc = min(minc, p.c);
        }

        for (auto p : v) {
            int r = p.r - minr;
            int c = p.c - minc;
            if (r >= 0 && r < 200 && c >= 0 && c < 200) {
                grid[r][c] = '#';
            }
        }

        bool ok = false;
        for (int r = 0; r < 200; ++r) {
            for (int c = 0; c < 200-3; ++c) {
                if (grid[r][c] == '#' && grid[r][c+1] == '#' && grid[r][c+2] == '#' && grid[r][c+3] == '#') ok=true;
            }
        }


        if (ok) {
            cout << i << endl;
            for (int r = 0; r < 200; ++r) {
                for (int c = 0; c < 200; ++c) {
                    cout << grid[r][c];
                }
                cout << endl;
            }
        }

        advance(v);
    }
}
