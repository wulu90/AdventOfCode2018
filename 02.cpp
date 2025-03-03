#include <fstream>
#include <map>
#include <string>

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

int main() {
    part1();
    return 0;
}
