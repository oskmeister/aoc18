#include <vector>
#include <iostream>

using namespace std;

vector<int> grid[1000][1000];

struct UF {
    vector<int> e;
	UF(int n) : e(n, -1) {}
	bool same_set(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	void join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
	}
};

int main() {
    int r, c, h, w;
    int id = 1;
    UF disjoint_set(2000);
    while (cin >> r >> c >> h >> w) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                for (auto x : grid[r+i][c+j]) {
                    disjoint_set.join(x, id);
                }
                grid[r+i][c+j].push_back(id);
            }
        }
        ++id;
    }
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            if (grid[i][j].size() == 1 && disjoint_set.size(grid[i][j][0]) == 1) {
                cout << grid[i][j][0] << endl;
            }
        }
    }
}
