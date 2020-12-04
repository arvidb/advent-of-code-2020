#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <unordered_map>

using namespace std;

pair<string, string> getKV(const string& s) {
    int pos = s.find_first_of(':');
    return {s.substr(0, pos), s.substr(pos+1)};
}

bool isValid(const unordered_map<string, string>& passport) {
    static const auto keys = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };
    return std::all_of(begin(keys), end(keys), [&passport](const auto& k) { return passport.count(k); });
}

int main() {

    auto nValid = 0;
    std::unordered_map<string, string> passport;
    for (string line; getline(cin, line);) {
        if (line.empty()) {

            if (isValid(passport))
                nValid++;

            passport.clear();
        }

        istringstream iss(line);
        vector<string> tokens { istream_iterator<string>{iss}, istream_iterator<string>{} };

        for (auto token : tokens) {
            auto kv = getKV(token);
            passport[kv.first] = kv.second;
        }
    }

    if (!passport.empty() && isValid(passport))
        nValid++;

    cout << nValid << endl;

    return 0;
}