#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int count(const vector<int> &before, const vector<int> &after, int opcode, int p1, int p2, int r) {
    int ret = 0;
    for (int i = 0; i < 2; ++i) {
        int val1 = before[p1];
        int val2 = before[p2];
        if (i == 1) val2 = p2;
        int res = after[r];
        if (val1 + val2 == res) ret++;
        if (val1 * val2 == res) ret++;
        if ((val1 | val2) == res) ret++;
        if ((val1 & val2) == res) ret++;
        if (i == 1) val1 = p1;
        if (val1 == res) ret++;
    }
    // ir
    if (p2 >= 0 && p2 < 4) {
        int val1 = p1;
        int val2 = before[p2];
        int res = after[r];
        if (((val1 > val2) ? 1 : 0) == res) {
            ret++;
        }
        if (((val1 == val2) ? 1 : 0) == res) {
            ret++;
        }
    }
    // ri
    if (p1 >= 0 && p1 < 4) {
        int val1 = before[p1];
        int val2 = p2;
        int res = after[r];
        if (((val1 > val2) ? 1 : 0) == res) {
            ret++;
        }
        if (((val1 == val2) ? 1 : 0) == res) {
            ret++;
        }
    }
    // rr
    if (p1 >= 0 && p1 < 4 && p2 >= 0 && p2 < 4) {
        int val1 = before[p1];
        int val2 = before[p2];
        int res = after[r];
        if (((val1 > val2) ? 1 : 0) == res) {
            ret++;
        }
        if (((val1 == val2) ? 1 : 0) == res) {
            ret++;
        }
    }
    return ret;
}

int main() {
    int a,b,c,d;
    int opcode, p1, p2, r;
    int ap, bp, cp, dp;
    int ans = 0;
    while (scanf("Before: [%d, %d, %d, %d]\n", &a, &b, &c, &d) == 4) {
        scanf("%d %d %d %d\n", &opcode, &p1, &p2, &r);
        scanf("After: [%d, %d, %d, %d]\n", &ap, &bp, &cp, &dp);
        vector<int> before = {a,b,c,d};
        vector<int> after = {ap,bp,cp,dp};
        int check = count(before, after, opcode, p1, p2, r);
        if (check >= 3) ++ans;
    }
    cout << ans << endl;
}
