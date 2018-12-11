#include <iostream>

using namespace std;

const long long input = 5791;

long long get_value(int X, int Y) {
    const long long rackid = X+10;
    long long tmp = rackid*Y+input;
    tmp = tmp * rackid;
    tmp = (tmp / 100) % 10;
    tmp -= 5;
    return tmp;
}

long long get_sum(int X, int Y, int sz) {
    long long ans = 0;
    for (int dx = 0; dx < sz; ++dx) {
        for (int dy = 0; dy < sz; ++dy) {
            ans += get_value(X+dx, Y+dy);
        }
    }
    return ans;
}

int main() {
    long long best = 0;
    int X, Y, SZ;
    for (int x = 1; x <= 300; ++x) {
        for (int y = 1; y <= 300; ++y) {
            for (int sz = 1; sz <= min(300-x, 300-y); ++sz) {
                long long ans_here = get_sum(x,y,sz);
                if (ans_here > best) {
                    X = x;
                    Y = y;
                    SZ = sz;
                    best = ans_here;
                }
            }
        }
    }
    cout << X << "," << Y << "," << SZ << endl;
}
