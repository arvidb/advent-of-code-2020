#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

long getLoops(int a, int b, int find=0, int m=20201227) {
    long result = 1;
    for (int i=1; i <= b; i++) {
        result = (result * a) % m;

        if (result == find)
            return i;
    }

    return result;
}

int main() {

    int p1, p2;
    cin >> p1 >> p2;

    long card = getLoops(7, 1000000000, p1);
    long door = getLoops(7, 1000000000, p2);

    cout << getLoops(p1, door) << endl;
}