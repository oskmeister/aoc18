#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector<char> neigh[100];
int in[100];
bool done[100];

char pop_node() {
    for (int i = 0; i < 32; ++i) {
        if (done[i]) continue;
        if (in[i] == 0) {
            done[i] = true;
            for (int n : neigh[i]) {
                in[n]--;
            }
            return 'A' + i;
        }
    }
    return 'a';
}

int main() {
    char a, b;
    while(scanf("Step %c must be finished before step %c can begin.\n", &a, &b) == 2) {
        cout << a << " " << b << endl;
        neigh[a-'A'].push_back(b-'A');
        in[b-'A']++;
    }
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        char ans = pop_node();
        cout << ans;
    }
    cout << endl;
}
