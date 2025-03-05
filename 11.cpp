#include <array>
#include <print>
#include <vector>

using namespace std;

int power_level(int x, int y, int serial) {
    int power_level = ((x + 10) * y + serial) * (x + 10);

    power_level = power_level < 100 ? 0 : (power_level / 100) % 10;

    power_level -= 5;
    return power_level;
}

int total_power(int x, int y, const array<array<int, 300>, 300>& grid) {
    int tp = 0;
    for (int i = x; i < x + 3; ++i) {
        for (int j = y; j < y + 3; ++j) {
            tp += grid[i][j];
        }
    }
    return tp;
}

void part1() {
    const int serial = 1955;

    array<array<int, 300>, 300> grid;

    for (int i = 0; i < 300; ++i) {
        for (int j = 0; j < 300; ++j) {
            grid[i][j] = power_level(i + 1, j + 1, serial);
        }
    }

    int largest_total_power = numeric_limits<int>::lowest();
    int x, y;
    for (int i = 0; i < 298; ++i) {
        for (int j = 0; j < 298; ++j) {
            int tp = total_power(i, j, grid);
            if (tp > largest_total_power) {
                largest_total_power = tp;
                x                   = i + 1;
                y                   = j + 1;
            }
        }
    }
    println("{},{}", x, y);
}

void part2() {
    const int serial = 1955;

    array<array<int, 300>, 300> grid;

    for (int i = 0; i < 300; ++i) {
        for (int j = 0; j < 300; ++j) {
            grid[i][j] = power_level(i + 1, j + 1, serial);
        }
    }

    // array<array<array<int, 300>, 300>, 300> grid3d;  too big array
    vector<int> grid_r(300, 0);
    vector<vector<int>> grid2d(300, grid_r);
    vector<vector<vector<int>>> grid3d(300, grid2d);

    for (int i = 0; i < 300; ++i) {
        for (int j = 0; j < 300; ++j) {
            grid3d[i][j][0] = grid[i][j];

            int square_size = min(300 - i, 300 - j);

            for (int k = 1; k < square_size; ++k) {
                int side_powers = 0;

                for (int a = 0; a < k; ++a) {
                    side_powers += grid[i + k][j + a] + grid[i + a][j + k];
                }
                side_powers += grid[i + k][j + k];
                grid3d[i][j][k] = grid3d[i][j][k - 1] + side_powers;
            }
        }
    }

    int largest_total_power = numeric_limits<int>::lowest();
    int x, y, n;
    for (int i = 0; i < 300; ++i) {
        for (int j = 0; j < 300; ++j) {
            for (int k = 0; k < 300; ++k) {
                if (grid3d[i][j][k] > largest_total_power) {
                    largest_total_power = grid3d[i][j][k];
                    x                   = i + 1;
                    y                   = j + 1;
                    n                   = k + 1;
                }
            }
        }
    }
    println("{},{},{}", x, y, n);
}

int main() {
    part1();
    part2();
    return 0;
}
