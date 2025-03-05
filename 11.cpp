#include <print>

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
                x                  = i + 1;
                y                  = j + 1;
            }
        }
    }
    println("{},{}", x, y);
}

int main() {
    part1();
    return 0;
}
