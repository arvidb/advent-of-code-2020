#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> getBags(string s) {
    const string delimiter = ", ";
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

bool containsBag(unordered_map<string, vector<pair<int, string>>>& m, const string& color) {
    if (m.count(color) == 0)  
        return false;
    return any_of(begin(m.at(color)), end(m.at(color)), [&](pair<int, string> tup) { return tup.second == "shiny gold" || containsBag(m, tup.second); });
}

int main() {

    unordered_map<string, vector<pair<int, string>>> bags;
    for (string line; getline(cin, line);) {

        int pos = line.find(" contain ");
        string top = line.substr(0, pos-1);
        top = top.substr(0, top.find_last_of(" "));

        string content = line.substr(pos+9);
        if (content != "no other bags.") {
            for (auto c : getBags(content)) {

                pos = c.find_first_of(" ");
                int amount = stoi(c.substr(0, pos));
                string color = c.substr(pos+1);
                color = color.substr(0, color.find_last_of(" "));

                bags[top].push_back({amount, color});
            }
        }
    }

    cout << count_if(begin(bags), end(bags), [&](auto kv) { return containsBag(bags, kv.first); }) << endl;
}