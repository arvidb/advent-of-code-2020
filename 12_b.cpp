#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <numeric>

using namespace std;

enum Direction { North, East, South, West };

struct Waypoint {
    int x = 10;
    int y = 1;
};

struct Ship {
    int x = 0;
    int y = 0;
    Waypoint waypoint;

    void turn(int degrees) {
        float angle = -degrees * (M_PI / 180);
        int xx = round(waypoint.x * cos(angle) - waypoint.y * sin(angle));
        int yy = round(waypoint.x * sin(angle) + waypoint.y * cos(angle));
        waypoint.x = xx;
        waypoint.y = yy;
    }

    void move(int amount) {
        x += waypoint.x * amount;
        y += waypoint.y * amount;
    }
};

int main() {

    Ship ship;
    for (string line; getline(cin, line);) {

        char ins = line[0];
        int amount = stoi(line.substr(1));

        switch (ins)
        {
        case 'N': ship.waypoint.y += amount; break;
        case 'S': ship.waypoint.y -= amount; break;
        case 'E': ship.waypoint.x += amount; break;
        case 'W': ship.waypoint.x -= amount; break;
        case 'L': ship.turn(-amount); break;
        case 'R': ship.turn(amount); break;
        case 'F': ship.move(amount); break;
        }
    }

    cout << abs(ship.x) + abs(ship.y) << endl;
}