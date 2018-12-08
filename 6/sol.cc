#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

using namespace std;

int grid[400][400];
vector<pair<int,int>> coords;
vector<bool> inf;

vector<int> find_closest(int r, int c) {
    int bestv = 1<<30;
    vector<int> best = vector<int>();
    for (int i = 0; i < coords.size(); ++i) {
        const int rp = coords[i].first;
        const int cp = coords[i].second;
        const int d = abs(r-rp) + abs(c-cp);
        if (d < bestv) {
            bestv = d;
            best = {i};
        } else if (d == bestv) {
            best.push_back(i);
        }
    }
    return best;
}

void mark(int r, int c) {
    auto v = find_closest(r, c);
    if (v.size() == 1) {
        int x = v[0];
        inf[x] = true;
    }
}

int main() {
    int r, c;
    while (scanf("%d, %d", &r, &c) == 2) {
        r++;
        c++;
        coords.push_back(make_pair(r,c));
        inf.push_back(false);
    }

    for (int i = 0; i < 400; ++i) {
        mark(i, 399);
        mark(399, i);
        mark(0, i);
        mark(i, 0);
    }

    map<int, int> counts;
    for (int i = 0; i < 400; ++i) {
        for (int j = 0; j < 400; ++j) {
            auto v = find_closest(i, j);
            if (v.size() == 1 && !inf[*v.begin()]) {
                counts[*v.begin()]++;
            }
        }
    }

    int best = -1;
    int bestv = 0;
    for (auto p : counts) {
        if (p.second > bestv) {
            best = p.first;
            bestv = p.second;
        }
    }
    cout << bestv << endl;
}
