#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

int main() {

    long sum = 0;
    unordered_set<char> q;
    for (string line; getline(cin, line);) {
        if (line.empty()) {
            sum += q.size();
            q.clear();
        }

        for (char c : line)
            q.insert(c);
    }
    
    sum += q.size();
    cout << sum << endl;
}