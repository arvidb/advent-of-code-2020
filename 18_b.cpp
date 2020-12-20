#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <numeric>

using namespace std;

long calc(list<string>& tokens) {
    bool hasAdd = true;
    while (hasAdd) {
        hasAdd = false;
        for (auto it = tokens.begin(); it != tokens.end(); it++) {
            if (*it == "+") {
                hasAdd = true;
                auto p = prev(it);
                auto n = next(it);
                long result = stol(*p) + stol(*n);
                *it = to_string(result);
                tokens.erase(p);
                tokens.erase(n);
            }
        }
    }

    while(tokens.size() > 2) {
        string a = tokens.front(); tokens.pop_front();
        string op = tokens.front(); tokens.pop_front();
        string b = tokens.front(); tokens.pop_front();

        long result = 0;
        if (op == "*") {
            result = stol(a) * stol(b);
            tokens.push_front(to_string(result));
        }
    }

    return stol(tokens.front());
}

int main() {

    long sum = 0;
    for (string line; getline(cin, line);) {
        list<string> tokens;
        for (auto c : line) {
            if (c != ' ') {
                if (c == ')') {

                    list<string> tmp;
                    while (tokens.back() != "(") {
                        tmp.push_front(tokens.back());
                        tokens.pop_back();
                    }
                    tokens.pop_back();
                
                    tokens.push_back(to_string(calc(tmp)));
                } else {

                    tokens.push_back(string(1, c));
                }
            }
        }

        sum += calc(tokens);
    }

    cout << sum << endl;
}