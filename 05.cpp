#include <fstream>
#include <string>

using namespace std;

void part1() {
    ifstream input("input/input05");
    string line;
    getline(input, line);

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

    println("{}", line.size());
}

int main() {
    part1();
    return 0;
}
