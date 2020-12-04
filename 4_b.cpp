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

    if (!std::all_of(begin(keys), end(keys), [&passport](const auto& k) { return passport.count(k); })) {
        return false;
    }

    bool valid = true;
    for (auto kv : passport) {
        if (kv.first == "byr") {
            auto val = stoi(kv.second);
            valid = val >= 1920 && val <= 2002;
        }
        else if (kv.first == "iyr") {
            auto val = stoi(kv.second);
            valid = val >= 2010 && val <= 2020;
        }
        else if (kv.first == "eyr") {
            auto val = stoi(kv.second);
            valid = val >= 2020 && val <= 2030;
        }
        else if (kv.first == "hgt") {
            if (kv.second.find("cm") != string::npos) {
                auto val = stoi(kv.second);
                valid = val >= 150 && val <= 193;
            } else if (kv.second.find("in") != string::npos) {
                auto val = stoi(kv.second);
                valid = val >= 59 && val <= 76;
            } else {
                valid = false;
            }
        }
        else if (kv.first == "hcl") {
            if (kv.second[0] != '#') {
                valid = false;
            } else {
                auto s = kv.second.substr(1);
                valid = s.length() == 6 && std::all_of(begin(s), end(s), [](auto c) { return isxdigit(c); });
            }
        }
        else if (kv.first == "ecl") {
            static const auto colors = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
            valid = 1 == std::count(begin(colors), end(colors), kv.second);
        }
        else if (kv.first == "pid") {
            valid = kv.second.length() == 9;
        }

        if (!valid) {
            return false;
        }
    }

    return true;
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
}