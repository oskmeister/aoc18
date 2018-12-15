#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include <numeric>

using namespace std;

int main() {
    string str;
    int active_guard;
    int last_wake;
    map<int, vector<int>> data;
    while (cin >> str) {
        int mm, g;
        if (str == "guard") {
            cin >> g >> mm;
            active_guard = g;
            if (!data.count(active_guard)) {
                data[active_guard] = vector<int>(60);
            }
        } else if (str == "wake") {
            cin >> mm;
            for (int i = last_wake; i < mm; ++i) {
                data[active_guard][i]++;
            }
        } else if (str == "fall") {
            cin >> mm;
            last_wake = mm;
        }
    }

    int most = -1;
    int most_v = 0;
    for (auto p : data) {
        auto &v = p.second;
        int sum = accumulate(v.begin(), v.end(), 0);
        if (sum > most_v) {
            most = p.first;
            most_v = sum;
        }
    }

    cout << most << endl;

    auto &v = data[most];
    cout << "One: " << most * distance(v.begin(), max_element(v.begin(), v.end())) << endl;


    cout << "Part two:" << endl;

    int ans_v = 0;
    int ans_minute = -1;
    int ans_g = -1;
    for (auto p : data) {
        int cur = *max_element(p.second.begin(), p.second.end());
        if (cur > ans_v) {
            ans_g = p.first;
            ans_v = cur;
            ans_minute = distance(p.second.begin(), max_element(p.second.begin(), p.second.end()));
        }
    }

    cout << ans_minute * ans_g << endl;

}
