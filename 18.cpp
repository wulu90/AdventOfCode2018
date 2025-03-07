#include <array>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "md5.h"

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

array<byte, 16> hash_acres(const vector<string>& acres) {
    string str;
    for (auto& s : acres) {
        str.append(s);
    }
    return md5_l(str);
}

void magic_change(vector<string>& acres) {
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

void part1() {
    ifstream input("input/input18");
    vector<string> acres;
    for (string line; getline(input, line);) {
        acres.push_back(line);
    }

    for (size_t minute = 1; minute <= 10; ++minute) {
        magic_change(acres);
    }

    auto [open, trees, lumberyard] = count_all(acres);
    println("{}", trees * lumberyard);
}

void part2() {
    ifstream input("input/input18");
    vector<string> acres;
    for (string line; getline(input, line);) {
        acres.push_back(line);
    }
    map<array<byte, 16>, size_t> hash_index;
    auto ori_hash = hash_acres(acres);
    for (size_t minute = 1; minute <= 1000000000; ++minute) {
        magic_change(acres);
        auto hs = hash_acres(acres);

        if (hash_index.contains(hs)) {
            minute = 1000000000 - (1000000000 - minute) % (minute - hash_index.at(hs));

        } else {
            hash_index.insert({hs, minute});
        }
    }

    auto [open, trees, lumberyard] = count_all(acres);
    println("{}", trees * lumberyard);
}

int main() {
    part1();
    part2();
    return 0;
}
