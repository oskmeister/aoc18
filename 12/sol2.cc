#include <iostream>

using namespace std;

int main() {
    long long target_iter = 50000000000LL;
    long long iter = 400;
    long long ans = 21666;
    long long diff = 53;
    cout << ans + (target_iter - iter)*diff << endl;
}
