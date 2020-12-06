#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <numeric>

using namespace std;


int main() {

    const function<int(const unordered_map<char, int>&, int)> ack = [](const auto& q, int p) {
        return accumulate(begin(q), end(q), 0, [&](int a, const auto& kv) { return a + (kv.second == p ? 1 : 0); });
    };
    long sum = 0;
    unordered_map<char, int> q;
    int p = 0;
    for (string line; getline(cin, line);) {
        if (line.empty()) {
            sum += ack(q, p);
            q.clear();
            p = 0;
        }
        else
        {
            for (char c : line)
                q[c] += 1;
            p++;
        }
        
    }

    sum += ack(q, p);
    cout << sum << endl;
}