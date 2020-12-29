#include <iostream>
#include <algorithm>
#include <numeric>
#include <string_view>
#include <optional>
#include <vector>
#include <array>

using namespace std;

constexpr int N = 512;
constexpr int M = N/2;
typedef array<array<bool, N>, N> map_t;

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

int getAdjacent(const map_t& map, pair<int, int> pos) {
    return accumulate(begin(DirLookup), end(DirLookup), 0, [&map, pos](int ack, auto d) { 
        return ack + map[pos.second + d.second][pos.first + d.first]; 
        });
}

int main() {

    map_t map = {{}};

    for (string line; getline(cin, line);) {
        pair<int, int> pos = {M, M};
        string_view str = line;
        for (auto dir = getNext(str); dir.has_value(); dir = getNext(str)) {
            move(pos, dir.value());
        }

        map[pos.second][pos.first] ^= 1; 
    }

    for (int day=0; day < 100; day++) {
        map_t newMap = map;
        for (int y=0; y < map.size(); y++) {
            for (int x=0; x < map[y].size(); x++) {
                int n = getAdjacent(map, {x, y});
                if (map[y][x] && (n == 0 || n > 2))
                    newMap[y][x] = false;
                else if (!map[y][x] && n == 2)
                    newMap[y][x] = true;
            }
        }

        map = newMap;
    }

    int count = 0;
    for (auto row : map) {
        for (auto col : row) {
            if (col)
                count += 1;
        }
    }

    cout << count << endl;
}