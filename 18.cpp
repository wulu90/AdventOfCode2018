#include <array>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

tuple<size_t, size_t, size_t> count_adjacents(const vector<string>& acres, size_t row, size_t col) {
    static const array<array<int, 2>, 8> deltas{{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}};
    size_t open       = 0;
    size_t trees      = 0;
    size_t lumberyard = 0;
    for (auto [dr, dc] : deltas) {
        auto r = row + dr;
        auto c = col + dc;
        if (r < acres.size() && c < acres.front().size()) {
            switch (acres[r][c]) {
            case '.':
                ++open;
                break;
            case '|':
                ++trees;
                break;
            case '#':
                ++lumberyard;
                break;
            }
        }
    }
    return {open, trees, lumberyard};
}

tuple<size_t, size_t, size_t> count_all(const vector<string>& acres) {
    size_t open       = 0;
    size_t trees      = 0;
    size_t lumberyard = 0;
    for (auto& row : acres) {
        for (auto& c : row) {
            switch (c) {
            case '.':
                ++open;
                break;
            case '|':
                ++trees;
                break;
            case '#':
                ++lumberyard;
                break;
            }
        }
    }
    return {open, trees, lumberyard};
}

void part1() {
    ifstream input("input/input18");
    vector<string> acres;
    for (string line; getline(input, line);) {
        acres.push_back(line);
    }

    for (int minute = 0; minute < 10; ++minute) {
        auto tmp = acres;

        for (size_t r = 0; r < acres.size(); ++r) {
            for (size_t c = 0; c < acres.front().size(); ++c) {
                auto [open, trees, lumberyard] = count_adjacents(acres, r, c);
                switch (acres[r][c]) {
                case '.':
                    tmp[r][c] = trees >= 3 ? '|' : '.';
                    break;
                case '|':
                    tmp[r][c] = lumberyard >= 3 ? '#' : '|';
                    break;
                case '#':
                    tmp[r][c] = lumberyard >= 1 && trees >= 1 ? '#' : '.';
                    break;
                }
            }
        }
        acres = std::move(tmp);
    }

    auto [open, trees, lumberyard] = count_all(acres);
    println("{}", trees * lumberyard);
}

int main() {
    part1();
    return 0;
}
