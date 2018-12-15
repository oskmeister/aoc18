#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    const int n_players = 427;
    const int last_marble = 7072300;

    vector<int> v = {0};
    vector<long long> scores(n_players, 0);

    int current_idx = 0;
    int current_player = 0;
    int current_marble = 1;

    for (int i = 0; i < last_marble; ++i) {
        if (i % 10000 == 0) {
            cout << double(i) / last_marble << endl;
        }
        if (current_marble % 23 == 0) {
            scores[current_player] += current_marble;
            current_idx = (current_idx - 7 + v.size()) % v.size();
            scores[current_player] += v[current_idx];
            v.erase(v.begin() + current_idx);
        } else {
            current_idx++;
            current_idx %= v.size();
            v.insert(v.begin() + current_idx + 1, current_marble);
            current_idx++;
        }
        current_player = (current_player + 1) % n_players;
        current_marble++;
    }


    cout << *max_element(scores.begin(), scores.end()) << endl;
}
