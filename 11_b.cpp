#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <numeric>

using namespace std;

int getAdjacent(const vector<string>& map, int x, int y) {
    int n = 0;
    for (auto i : {-1, 0, 1}) {
        for (auto j : {-1, 0, 1}) {
            int xi = x+i;
            int yj = y+j;

            if (xi == x && yj == y) {
                continue;
            }

            while (xi >= 0 && xi < map[0].size() &&
                   yj >= 0 && yj < map.size()) {

                if (map[yj][xi] == '#') {
                    n++;
                    break;
                }
                else if (map[yj][xi] != '.') {
                    break;
                }
                xi += i;
                yj += j;
            }
        }
    }

    return n;
}

int main() {

    vector<string> map;
    for (string line; getline(cin, line);) {
        map.push_back(line);
    }

    bool change = true;
    while (change) {
        change = false;

        vector<string> newMap = map;
        for (int x=0; x < map[0].size(); x++) {
            for (int y=0; y < map.size(); y++) {

                auto n = getAdjacent(map, x, y);
                if (newMap[y][x] == 'L' && n == 0) {
                    newMap[y][x] = '#';
                    change = true;
                }
                else if (map[y][x] == '#' && n >= 5) {
                    newMap[y][x] = 'L';
                    change = true;
                }
            }
        }

        map = newMap;
    }

    int result = 0;
    for (auto row : map) {
        result += count(begin(row), end(row), '#');
    }

    cout << result << endl;
}