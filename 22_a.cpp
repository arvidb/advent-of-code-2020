#include <iostream>
#include <algorithm>
#include <queue>
#include <numeric>

using namespace std;

int main() {

    queue<int> player1, player2;
    int player = 0;
    for (string line; getline(cin, line);) {
        if (line.empty())
            continue;

        if (line.find("Player") != string::npos) {
            player++;
        }
        else if (player == 1) {
            player1.push(stoi(line));
        }
        else if (player == 2) {
            player2.push(stoi(line));
        }
    }

    while (!player1.empty() && !player2.empty()) {
        int p1 = player1.front(); player1.pop();
        int p2 = player2.front(); player2.pop();
        if (p1 > p2) {
            player1.push(max(p1, p2));
            player1.push(min(p1, p2));
        }
        else {
            player2.push(max(p1, p2));
            player2.push(min(p1, p2));
        }
    }

    int score = 0;
    while (!player1.empty()) {
        score += (player1.front() * player1.size());
        player1.pop();
    }
    while (!player2.empty()) {
        score += (player2.front() * player2.size());
        cout << "+ " << player2.front() << " " << player2.size() << endl;
        player2.pop();
    }
    cout << score << endl;
}