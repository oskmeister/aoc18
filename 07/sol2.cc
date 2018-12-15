#include <cstdio>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<int> neigh[100];
int in[100];
bool taken[100];
bool done[100];
set<char> input_set;

void mark_done(int i) {
    done[i] = true;
    for (int n : neigh[i]) {
        in[n]--;
    }
}

char pop_node() {
    for (auto c : input_set) {
        int i = c - 'A';
        if (taken[i] || done[i]) continue;
        if (in[i] == 0) {
            return 'A' + i;
        }
    }
    return 'a';
}

int main() {
    char a, b;
    while(scanf("Step %c must be finished before step %c can begin.\n", &a, &b) == 2) {
        neigh[a-'A'].push_back(b-'A');
        in[b-'A']++;
        input_set.insert(a);
        input_set.insert(b);
    }

    vector<pair<char,int>> workers(5);
    for (int i = 0; i < 5; ++i) workers[i].first = 'a';
    int t = 0;

    int num_done = 0;
    for (;;) {
        cout << "t = " << t << endl;
        // Look for jobs
        for (int i = 0; i < 5; ++i) {
            if (workers[i].first == 'a') {
                char ans = pop_node();
                if (ans == 'a') break;
                taken[ans-'A'] = true;
                workers[i].first = ans;
                workers[i].second = 60 + (ans - 'A' + 1);
                cout << i << " picked up " << workers[i].first << endl;
            }
        }

        // Do work
        for (int i = 0; i < 5; ++i) {
            if (workers[i].first != 'a' && workers[i].second > 0) workers[i].second--;
        }

        // Finish work
        for (int i = 0; i < 5; ++i) {
            if (workers[i].first != 'a') {
                if (workers[i].second == 0) {
                    num_done++;
                    mark_done(workers[i].first - 'A');
                    char tmp = workers[i].first;
                    cout << workers[i].first;
                    workers[i].first = 'a';
                    if (num_done == input_set.size()) {
                        cout << t+1 << endl;
                        return 0;
                    }
                }
            }
        }

        ++t;
    }

}
