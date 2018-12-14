#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int input = 990941;
    vector<int> v = {3, 7};
    int a = 0;
    int b = 1;
    for (;;) {
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
        if (v.size() >= input + 10) {
            for (int j = input; j < input + 10; ++j) {
                cout << v[j];
            }
            cout << endl;
            return 0;
        }
    }
}
