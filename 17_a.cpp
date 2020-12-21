#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <array>
#include <numeric>
#include <regex>

using namespace std;
constexpr int N = 64;
constexpr int O = N/2;

typedef array<array<array<char, N>, N>, N> matrix_t;

bool isActive(matrix_t& matrix, int x, int y, int z) {
    if (x < 0 || y < 0 || z < 0)
        return false;
    if (x >= N || y >= N || z >= N)
        return false;

    return matrix[x][y][z] == '#';
}

int activeNeighbors(matrix_t& matrix, int x, int y, int z) {
    int sum = 0;
    for (auto xx : {-1, 0, 1}) {
        for (auto yy : {-1, 0, 1}) {
            for (auto zz : {-1, 0, 1}) {
                if (xx == 0 && yy == 0 && zz == 0)
                    continue;

                if (isActive(matrix, x+xx, y+yy, z+zz))
                    sum++;
            }
        }
    }
    return sum;
}

int main() {

    matrix_t matrix;
    int y=0;
    int z=0;
    for (string line; getline(cin, line); y++) {
        for (int x=0; x < line.length(); x++) {
            matrix[O+x][O+y][O+z] = line[x];
        }
    }

    matrix_t matrix2 = matrix;
    for (int cycle=0; cycle < 6; cycle++) {
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < N; y++) {
                for (int z = 0; z < N; z++) {

                    int n = activeNeighbors(matrix, x, y, z);
                    if (isActive(matrix, x, y, z) && (n < 2 || n > 3)) {
                        matrix2[x][y][z] = '.';
                    }
                    else if (!isActive(matrix, x, y, z) && (n == 3)) {
                        matrix2[x][y][z] = '#';
                    }
                }
            }
        }

        matrix = matrix2;
    }

    int active = 0;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            for (int z = 0; z < N; z++) {
                if (isActive(matrix, x, y, z)) {
                    active++;
                }
            }
        }
    }

    cout << active << endl;
}