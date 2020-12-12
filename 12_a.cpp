#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <numeric>

using namespace std;

enum Direction { North, East, South, West };

struct Ship {
    int x = 0;
    int y = 0;
    Direction facing = Direction::East;

    void turn(int degrees) {
        int i = (facing + (degrees/90));
        facing = (Direction)((i % 4 + 4) % 4);
    }

    void move(int amount) {
        vector<pair<int, int>> d = { {0,1}, {1,0}, {0,-1}, {-1,0} };
        x += d[facing].first * amount;
        y += d[facing].second * amount;
    }
};

int main() {

    Ship ship;
    for (string line; getline(cin, line);) {

        char ins = line[0];
        int amount = stoi(line.substr(1));

        switch (ins)
        {
        case 'N': ship.y += amount; break;
        case 'S': ship.y -= amount; break;
        case 'E': ship.x += amount; break;
        case 'W': ship.x -= amount; break;
        case 'L': ship.turn(-amount); break;
        case 'R': ship.turn(amount); break;
        case 'F': ship.move(amount); break;
        }
    }

    cout << abs(ship.x) + abs(ship.y) << endl;
}