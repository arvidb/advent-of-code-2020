#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <functional>

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

    unordered_map<string, function<bool(string)>> validators = {
        {"cid", [](auto s) { return true; }},
        {"byr", [](auto s) { auto val = stoi(s); return val >= 1920 && val <= 2002; }},
        {"iyr", [](auto s) { auto val = stoi(s); return val >= 2010 && val <= 2020; }},
        {"eyr", [](auto s) { auto val = stoi(s); return val >= 2020 && val <= 2030; }},
        {"pid", [](auto s) { return s.length() == 9; }},
        {"ecl", [](auto s) { 
            static const auto colors = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
            return std::count(begin(colors), end(colors), s);
        }},
        {"hcl", [](auto s) { 
            if (s[0] != '#') {
                return false;
            } else {
                auto str = s.substr(1);
                return str.length() == 6 && std::all_of(begin(str), end(str), [](auto c) { return isxdigit(c); });
            }
         }},
        {"hgt", [](auto s) { 
            if (s.find("cm") != string::npos) {
                auto val = stoi(s);
                return val >= 150 && val <= 193;
            } else if (s.find("in") != string::npos) {
                auto val = stoi(s);
                return val >= 59 && val <= 76;
            } else {
                return false;
            }
        }}
    };

    return all_of(begin(passport), end(passport), [&](auto kv) { return validators[kv.first](kv.second); });
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