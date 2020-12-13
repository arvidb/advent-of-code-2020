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

    uint64_t time;
    string buses;

    cin >> time >> buses;

    vector<string> B;
    for (auto b : parse(buses)) {
        B.push_back(b);
    }

    uint64_t step = stoi(B[0]);
    time = step;

    for (int i=1; i < B.size();) {
        if (B[i] == "x") {
            i++;
            continue;
        }

        int b = stoi(B[i]);
        if ((time + i) % b == 0) {
            step *= b;
            i += 1;   
        } else {
            time += step;
        }
    }

    cout << time << endl;
}