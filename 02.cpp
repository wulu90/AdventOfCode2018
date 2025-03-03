#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void part1() {
    ifstream input("input/input02");
    int num2 = 0;
    int num3 = 0;
    for (string line; getline(input, line);) {
        map<char, size_t> char_count;
        for (auto c : line) {
            ++char_count[c];
        }

        for (auto [_, n] : char_count) {
            if (n == 2) {
                ++num2;
                break;
            }
        }

        for (auto [_, n] : char_count) {
            if (n == 3) {
                ++num3;
                break;
            }
        }
    }

    println("{}", num2 * num3);
}

size_t hamming_distance(const string& lhs, const string& rhs) {
    if (lhs.size() != rhs.size()) {
        return numeric_limits<size_t>::max();
    }
    size_t dist = 0;
    for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) {
            ++dist;
        }
    }
    return dist;
}

void part2() {
    ifstream input("input/input02");
    vector<string> id_vec;
    for (string line; getline(input, line);) {
        id_vec.push_back(line);
    }

    for (size_t i = 0; i < id_vec.size() - 1; ++i) {
        for (size_t j = i + 1; j < id_vec.size(); ++j) {
            if (hamming_distance(id_vec[i], id_vec[j]) == 1) {
                string common;
                for (size_t k = 0; k < id_vec[i].size(); ++k) {
                    if (id_vec[i][k] == id_vec[j][k]) {
                        common.push_back(id_vec[i][k]);
                    }
                }
                println("{}", common);
                break;
            }
        }
    }
}

int main() {
    part1();
    part2();
    return 0;
}
