#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <array>
#include <numeric>
#include <regex>

using namespace std;
constexpr int N = 32;
constexpr int O = N/2;

typedef array<array<array<array<char, N>, N>, N>, N> matrix_t;

bool isActive(matrix_t& matrix, int x, int y, int z, int w) {
    if (x < 0 || y < 0 || z < 0 || w < 0)
        return false;
    if (x >= N || y >= N || z >= N || w >= N)
        return false;

    return matrix[x][y][z][w] == '#';
}

int activeNeighbors(matrix_t& matrix, int x, int y, int z, int w) {
    int sum = 0;
    for (auto xx : {-1, 0, 1}) {
        for (auto yy : {-1, 0, 1}) {
            for (auto zz : {-1, 0, 1}) {
                for (auto ww : {-1, 0, 1}) {
                    if (xx == 0 && yy == 0 && zz == 0 && ww == 0)
                        continue;

                    if (isActive(matrix, x+xx, y+yy, z+zz, w+ww))
                        sum++;
                }
            }
        }
    }
    return sum;
}

int main() {

    matrix_t matrix;
    int y=0;
    for (string line; getline(cin, line); y++) {
        for (int x=0; x < line.length(); x++) {
            matrix[O+x][O+y][O][O] = line[x];
        }
    }

    matrix_t matrix2 = matrix;
    for (int cycle=0; cycle < 6; cycle++) {
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < N; y++) {
                for (int z = 0; z < N; z++) {
                    for (int w = 0; w < N; w++) {

                        int n = activeNeighbors(matrix, x, y, z, w);
                        if (isActive(matrix, x, y, z, w) && (n < 2 || n > 3)) {
                            matrix2[x][y][z][w] = '.';
                        }
                        else if (!isActive(matrix, x, y, z, w) && (n == 3)) {
                            matrix2[x][y][z][w] = '#';
                        }
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
                for (int w = 0; w < N; w++) {
                    if (isActive(matrix, x, y, z, w)) {
                        active++;
                    }
                }
            }
        }
    }

    cout << active << endl;
}