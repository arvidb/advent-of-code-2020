#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <numeric>

using namespace std;

int main() {

    vector<int> nums;
    for (string line; getline(cin, line, ',');) {
        nums.push_back(stoi(line));
    }

    for (auto target : {2020, 30000000}) {
        unordered_map<int, int> mem;

        for (int i=0; i < nums.size(); i++) {
            mem[nums[i]] = i+1;
        }

        int current = nums.back();
        int prev = 0;
        for (int turn=nums.size(); turn < target; turn++) {
            if (mem.count(current)) {
                prev = current;
                current = turn - mem[prev];
                mem[prev] = turn;
            } else {
                mem[current] = turn;
                current = 0;
            }
        }

        cout << current << endl;
    }
}