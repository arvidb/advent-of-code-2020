#include <iostream>
#include <array>
#include <string_view>
#include <algorithm>
#include <unordered_map>
#include <functional>

using namespace std;

const unordered_map<char, function<void(int&, int&)>> operations = {
    {'B', [](auto& l, auto& h) { auto d = h-l; l += d/2 + 1; }},
    {'F', [](auto& l, auto& h) { auto d = h-l; h = l + d/2;}},
    {'R', [](auto& l, auto& h) { auto d = h-l; l += d/2 + 1; }},
    {'L', [](auto& l, auto& h) { auto d = h-l; h = l + d/2;}},
};

long getRow(const string_view line) {

    pair<int, int> row = {0, 127};
    for (char c : line) {
        operations.at(c)(row.first, row.second);

        if (row.first == row.second)
            break;
    }
    
    return row.first;
}

long getColumn(const string_view line) {

    pair<int, int> col = {0, 7};
    for (char c : line) {

        operations.at(c)(col.first, col.second);

        if (col.first == col.second)
            break;
    }
    
    return col.first;
}

int main() {

    array<array<bool, 8>, 128> plane = {};

    for (string line; getline(cin, line);) {
        auto row = getRow(line.substr(0, 7));
        auto col = getColumn(line.substr(7, 8));
        plane[row][col] = true;
    }

    for (int row=1; row < plane.size()-1; row++) {
        for (int col=0; col < plane[row].size(); col++) {

            if (!plane[row][col]) {
                // Found empty seat, make sure seat infront and back is ocupied
                if (plane[row-1][col] && plane[row+1][col])
                    cout << "Found: " << (row*8) + col << endl;
            }
        }
    }
}