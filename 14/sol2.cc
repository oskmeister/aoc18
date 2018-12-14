#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int limit = 40000000;
    int input = 990941;
    vector<int> v = {3, 7};
    int a = 0;
    int b = 1;
    for (int i = 0; i < limit; ++i) {
        int sum = v[a] + v[b];
        {
            vector<int> tmp;
            if (sum == 0) tmp.push_back(0);
            else while (sum) {
                tmp.push_back(sum % 10);
                sum /= 10;
            }
            reverse(tmp.begin(), tmp.end());
            for (int x : tmp) {
                v.push_back(x);
            }
            a = (a + v[a] + 1) % v.size();
            b = (b + v[b] + 1) % v.size();
        }
    }
    for (int i = 0; i < v.size()-6; ++i) {
        int s = 0;
        for (int j = 0; j < 6; ++j) {
            s = s*10 + v[i+j];
        }
        if (s == input) {
            cout << i << endl;
            return 0;
        }
    }
}
