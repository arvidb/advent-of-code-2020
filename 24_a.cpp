#include <iostream>
#include <algorithm>
#include <numeric>
#include <string_view>
#include <optional>
#include <vector>
#include <array>
#include <map>

using namespace std;

enum class Direction {
    E, W, SE, SW, NW, NE
};

vector<pair<int, int>> DirLookup = {
    // axial-coords [q, r]
    {1, 0}, {-1, 0}, {0, 1}, {-1, 1}, {0, -1}, {1, -1}
};

optional<Direction> getNext(string_view& str) {
    auto tmp = str.substr(0, 2);
    if (tmp[0] == 'e') {
        str.remove_prefix(1);
        return Direction::E;
    }
    else if (tmp[0] == 'w') {
        str.remove_prefix(1);
        return Direction::W;
    }
    else if (tmp == "se") {
        str.remove_prefix(2);
        return Direction::SE;
    }
    else if (tmp == "sw") {
        str.remove_prefix(2);
        return Direction::SW;
    }
    else if (tmp == "nw") {
        str.remove_prefix(2);
        return Direction::NW;
    }
    else if (tmp == "ne") {
        str.remove_prefix(2);
        return Direction::NE;
    }

    return nullopt;
}

void move(pair<int, int>& pos, Direction dir) {
    auto d = DirLookup[static_cast<int>(dir)];
    pos.first += d.first;
    pos.second += d.second;
}

int main() {

    map<pair<int, int>, int> flips;

    for (string line; getline(cin, line);) {
        pair<int, int> pos = {};
        string_view str = line;
        for (auto dir = getNext(str); dir.has_value(); dir = getNext(str)) {
            move(pos, dir.value());
        }

        flips[pos] += 1; 
    }

    int sum = accumulate(begin(flips), end(flips), 0, [](int ack, auto kv) { return ack + kv.second % 2; });
    cout << sum << endl;
}