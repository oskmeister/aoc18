#include <iostream>
#include <vector>
#include <map>
#include <cstdio>

using namespace std;

// right, down, left, up
const int dr[4] = {0, 1, 0, -1};
const int dc[4] = {1, 0, -1, 0};

struct Cart {
    int id, r, c, dir, next_turn;
    bool crashed;
};

vector<string> grid;
vector<Cart> carts;

void process() {
    int cart_id = 0;
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            if (grid[r][c] == '>') {
                carts.push_back({cart_id++, r, c, 0, -1});
                grid[r][c] = '-';
            }
            if (grid[r][c] == 'v') {
                carts.push_back({cart_id++, r, c, 1, -1});
                grid[r][c] = '|';
            }
            if (grid[r][c] == '<') {
                carts.push_back({cart_id++, r, c, 2, -1});
                grid[r][c] = '-';
            }
            if (grid[r][c] == '^') {
                carts.push_back({cart_id++, r, c, 3, -1});
                grid[r][c] = '|';
            }
        }
    }
}

bool step() {
    sort(carts.begin(), carts.end(), [](const Cart &c1, const Cart &c2) {
        if (c1.r != c2.r) return c1.r < c2.r;
        return c1.c < c2.c;
    });

    for (int i = 0; i < carts.size(); ++i) {
        int nr = carts[i].r + dr[carts[i].dir];
        int nc = carts[i].c + dc[carts[i].dir];
        bool crashed = false;
        for (int j = 0; j < carts.size(); ++j) {
            // Collision check
            if (carts[j].r == nr && carts[j].c == nc) {
                crashed = true;
                carts[j].crashed = true;
                carts[i].crashed = true;
            }
        }
        if (crashed) continue;

        // Move
        carts[i].r = nr;
        carts[i].c = nc;

        // Check for intersection
        if (grid[nr][nc] == '+') {
            int next_turn;
            int ddr = carts[i].next_turn;
            if (ddr == -1) next_turn = 0;
            if (ddr == 0) next_turn = 1;
            if (ddr == 1) next_turn = -1;
            int ndr = (carts[i].dir + ddr + 4) % 4;
            carts[i].dir = ndr;
            carts[i].next_turn = next_turn;
        } else if (grid[nr][nc] == '/' || grid[nr][nc] == '\\') {
            if (carts[i].dir == 0 && grid[nr][nc] == '/') {
                carts[i].dir = (carts[i].dir - 1 + 4) % 4;
            }
            else if (carts[i].dir == 0 && grid[nr][nc] == '\\') {
                carts[i].dir = (carts[i].dir + 1) % 4;
            }
            else if (carts[i].dir == 1 && grid[nr][nc] == '/') {
                carts[i].dir = (carts[i].dir + 1) % 4;
            }
            else if (carts[i].dir == 1 && grid[nr][nc] == '\\') {
                carts[i].dir = (carts[i].dir - 1 + 4) % 4;
            }
            else if (carts[i].dir == 2 && grid[nr][nc] == '/') {
                carts[i].dir = (carts[i].dir - 1 + 4) % 4;
            }
            else if (carts[i].dir == 2 && grid[nr][nc] == '\\') {
                carts[i].dir = (carts[i].dir + 1) % 4;
            }
            else if (carts[i].dir == 3 && grid[nr][nc] == '/') {
                carts[i].dir = (carts[i].dir + 1) % 4;
            }
            else if (carts[i].dir == 3 && grid[nr][nc] == '\\') {
                carts[i].dir = (carts[i].dir - 1 + 4) % 4;
            }
        }
    }

    vector<Cart> new_carts;
    for (int i = 0; i < carts.size(); ++i) {
        if (carts[i].crashed) continue;
        new_carts.push_back(carts[i]);
    }
    carts = new_carts;

    if (carts.size() == 1) {
        auto cart = carts[0];
        cout << cart.c << "," << cart.r << endl;
        return true;
    }
    /*
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            bool found_cart = false;
            for (Cart &cart : carts) {
                if (cart.r == r && cart.c == c) {
                    found_cart = true;
                    int dir = cart.dir;
                    if (dir == 0) {
                        cout << '>';
                    } else if (dir == 1) {
                        cout << 'v';
                    } else if (dir == 2) {
                        cout << '<';
                    } else {
                        cout << '^';
                    }
                }
            }
            if (!found_cart) cout << grid[r][c];
        }
        cout << endl;
    }
    */
    return false;
}


int main() {
    {
        string input;
        while (getline(cin, input)) {
            grid.push_back(input);
        }
    }
    process();
    for (;;) {
        bool ok = step();
        if (ok) break;
    }
}
