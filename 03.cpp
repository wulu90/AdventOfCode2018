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

tuple<int, int, int, int, int> parse(const string& line) {
    int id, r, c, w, h;
    sscanf(line.data(), "#%d @ %d,%d: %dx%d", &id, &c, &r, &w, &h);

    return {id, c, r, w, h};
}

bool overlap(const tuple<int, int, int, int, int>& lhs, const tuple<int, int, int, int, int>& rhs) {
    auto [id_l, c_l, r_l, w_l, h_l] = lhs;
    auto [id_r, c_r, r_r, w_r, h_r] = rhs;

    return !(c_l + w_l <= c_r || c_r + w_r <= c_l || r_l + h_l <= r_r || r_r + h_r <= r_l);
}

void part2() {
    ifstream input("input/input03");
    vector<tuple<int, int, int, int, int>> claim_vec;
    for (string line; getline(input, line);) {
        claim_vec.push_back(parse(line));
    }

    for (size_t i = 0; i < claim_vec.size(); ++i) {
        bool has_overlap = false;
        for (size_t j = 0; j < claim_vec.size(); ++j) {
            if (i == j)
                continue;
            if (overlap(claim_vec[i], claim_vec[j])) {
                has_overlap = true;
                break;
            }
        }
        if (!has_overlap) {
            println("{}", get<0>(claim_vec[i]));
            break;
        }
    }
}

int main() {
    part1();
    part2();
    return 0;
}
