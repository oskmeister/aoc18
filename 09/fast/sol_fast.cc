#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    const int n_players = 9;
    const int last_marble = 25;

    list<int> v = {0};
    vector<long long> scores(n_players, 0);

    auto it = v.begin();
    int current_player = 0;
    int current_marble = 1;

    for (int i = 0; i < last_marble; ++i) {
        if (current_marble % 23 == 0) {
            scores[current_player] += current_marble;
            for (int j = 0; j < 7; ++j) {
                if (it == v.begin()) it = v.end();
                --it;
            }
            scores[current_player] += *it;
            it = v.erase(it);
        } else {
            for (int j = 0; j < 2; ++j) {
                ++it;
                if (it == v.end()) it = v.begin();
            }
            it = v.insert(it, current_marble);
        }
        current_player = (current_player + 1) % n_players;
        current_marble++;
    }


    cout << *max_element(scores.begin(), scores.end()) << endl;
}
