#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <vector>
#include <numeric>

using namespace std;

vector<string> parse(string s) {
    const string delimiter = ",";
    size_t pos = 0;
    vector<string> tokens;
    while ((pos = s.find(delimiter)) != string::npos) {
        tokens.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    if (!s.empty())
        tokens.push_back(s);

    return tokens;
}


int main() {

    int time;
    string buses;

    cin >> time >> buses;

    map<int, int> closest;
    for (auto b : parse(buses)) {
        if (b == "x")
            continue;

        int x = stoi(b);
        int n = time + (x - (time % x));
        closest[n-time] = x;
    }

    cout << closest.begin()->first * closest.begin()->second << endl;
}