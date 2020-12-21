#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <numeric>
#include <regex>

using namespace std;

pair<string, string> split(const string& s, char delimiter) {
    int pos = s.find_first_of(delimiter);
    return {s.substr(0, pos), s.substr(pos+1)};
}

int main() {

    map<int, string> rules;
    vector<string> lines;
    vector<string> messages;
    bool readingRules = true;
    for (string line; getline(cin, line);) {
        if (line.empty()) {
            readingRules = false;
            continue;
        }

        if (readingRules) {
            auto [a, b] = split(line, ':');
            if (b.find('"') != string::npos)
                rules[stoi(a)] = b.substr(2, 1);
            else
                lines.push_back(line);
        } else {
            messages.push_back(line);
        }
    }

    while(!lines.empty()) {
        vector<string> left;
        for (string line : lines) {
            auto [a, b] = split(line, ':');
            istringstream iss;
            iss.str(b);
            for (string rule; getline(iss, rule, ' ');) {

                if (!rule.empty()) {
                    if (rule == "|") {
                        rules[stoi(a)] += rule;
                    } else {
                        if (rules.count(stoi(rule))) {
                            auto tmp = rules[stoi(rule)];
                            if (tmp.length() != 1) {
                                tmp = "(" + tmp + ")";
                            }

                            if (rules.count(stoi(a))) {
                                rules[stoi(a)] += tmp;
                            } else {
                                rules[stoi(a)] = tmp;
                            }
                        } else {
                            rules.erase(stoi(a));
                            left.push_back(line);
                            break;
                        }
                    }
                }
            }
        }

        lines = left;
    }

    regex r {rules[0] + "$"};
    smatch match;

    cout 
        << count_if(begin(messages), end(messages), [&](auto msg) { return regex_match(msg, match, r); }) 
        << endl;
}