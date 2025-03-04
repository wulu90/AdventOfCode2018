#include <fstream>
#include <string>

using namespace std;

string reaction(string line) {
    while (true) {
        string tmp;
        size_t i;
        size_t destroy = 0;
        for (i = 0; i < line.size() - 1; ++i) {
            if (line[i] - line[i + 1] == 32 || line[i] - line[i + 1] == -32) {
                ++i;
                ++destroy;
            } else {
                tmp.push_back(line[i]);
            }
        }
        if (i == line.size() - 1) {
            tmp.push_back(line[i]);
        }
        if (destroy == 0) {
            break;
        }

        line = std::move(tmp);
    }
    return line;
}

void part1() {
    ifstream input("input/input05");
    string line;
    getline(input, line);
    println("{}", reaction(line).size());
}

void part2() {
    ifstream input("input/input05");
    string line;
    getline(input, line);
    array<size_t, 26> len_arr;

    for (int i = 0; i < 26; ++i) {
        string line_removed;
        for (auto& c : line) {
            if (c != 'a' + i && c != 'A' + i) {
                line_removed.push_back(c);
            }
        }

        len_arr[i] = reaction(line_removed).size();
    }

    println("{}", *min_element(len_arr.begin(), len_arr.end()));
}

int main() {
    part1();
    part2();
    return 0;
}
