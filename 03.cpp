#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> all_coords(const string& line) {
    int id, r, c, w, h;
    sscanf(line.data(), "#%d @ %d,%d: %dx%d", &id, &c, &r, &w, &h);
    vector<pair<int, int>> coords;
    for (int i = r; i < r + h; ++i) {
        for (int j = c; j < c + w; ++j) {
            coords.push_back({i, j});
        }
    }
    return coords;
}

void part1() {
    ifstream input("input/input03");
    map<pair<int, int>, int> coord_num;
    for (string line; getline(input, line);) {
        for (auto co : all_coords(line)) {
            ++coord_num[co];
        }
    }
    int overlap = 0;
    for (auto [_, n] : coord_num) {
        if (n > 1) {
            ++overlap;
        }
    }
    println("{}", overlap);
}

int main() {
    part1();
    return 0;
}
