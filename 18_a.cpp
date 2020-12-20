#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <deque>
#include <numeric>

using namespace std;

long calc(deque<string>& tokens) {
    while(tokens.size() > 2) {
        string a = tokens.front(); tokens.pop_front();
        string op = tokens.front(); tokens.pop_front();
        string b = tokens.front(); tokens.pop_front();
        
        long result = 0;
        if (op == "+")
            result = stol(a) + stol(b);
        else if (op == "*")
            result = stol(a) * stol(b);

        tokens.push_front(to_string(result));
    }

    return stol(tokens.front());
}

int main() {

    long sum = 0;
    for (string line; getline(cin, line);) {
        deque<string> tokens;
        for (auto c : line) {
            if (c != ' ') {
                if (c == ')') {

                    deque<string> tmp;
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