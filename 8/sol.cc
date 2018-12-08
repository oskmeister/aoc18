#include <iostream>

using namespace std;

int read() {
    int ans = 0;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) ans += read();
    for (int i = 0; i < m; ++i) {
        int mi;
        cin >> mi;
        ans += mi;
    }
    return ans;
}

int main() {
    cout << read() << endl;
}
