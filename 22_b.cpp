#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <deque>
#include <numeric>

using namespace std;

deque<int> copyQueue(deque<int> org, int maxSize) {
    while (org.size() > maxSize) {
        org.pop_back();
    }

    return org;
}

bool play(deque<int>& player1, deque<int>& player2) {
    vector<deque<int>> rounds1;
    vector<deque<int>> rounds2;
    while (!player1.empty() && !player2.empty()) {

        if (find(begin(rounds1), end(rounds1), player1) != end(rounds1)) {
            if (find(begin(rounds2), end(rounds2), player2) != end(rounds2)) {
                return true;
            }
        }
        rounds1.push_back(player1);
        rounds2.push_back(player2);

        int p1 = player1.front(); player1.pop_front();
        int p2 = player2.front(); player2.pop_front();

        if (p1 <= player1.size() && p2 <= player2.size()) {
            auto copy1 = copyQueue(player1, p1);
            auto copy2 = copyQueue(player2, p2);
            if (play(copy1, copy2)) {
                player1.push_back(p1);
                player1.push_back(p2);
            } else {
                player2.push_back(p2);
                player2.push_back(p1);
            }
        }
        else if (p1 > p2) {
            player1.push_back(p1);
            player1.push_back(p2);
        }
        else {
            player2.push_back(p2);
            player2.push_back(p1);
        }
    }

    return player2.empty();
}

int main() {

    deque<int> player1, player2;
    int player = 0;
    for (string line; getline(cin, line);) {
        if (line.empty())
            continue;

        if (line.find("Player") != string::npos) {
            player++;
        }
        else if (player == 1) {
            player1.push_back(stoi(line));
        }
        else if (player == 2) {
            player2.push_back(stoi(line));
        }
    }

    play(player1, player2);

    int score = 0;
    while (!player1.empty()) {
        score += (player1.front() * player1.size());
        player1.pop_front();
    }
    while (!player2.empty()) {
        score += (player2.front() * player2.size());
        player2.pop_front();
    }
    cout << score << endl;
}