#include <iostream>
#include <vector>

using namespace std;

int read() {
    int n, m;
    cin >> n >> m;
    int ans = 0;
    if (n == 0) {
        for (int i = 0; i < m; ++i) {
            int mi;
            cin >> mi;
            ans += mi;
        }
    } else {
        vector<int> v;
        for (int i = 0; i < n; ++i) v.push_back(read());
        for (int i = 0; i < m; ++i) {
            int mi;
            cin >> mi;
            mi--;
            if (mi >= 0 && mi < v.size()) {
                ans += v[mi];
            }
        }
    }
    return ans;
}

int main() {
    cout << read() << endl;
}
