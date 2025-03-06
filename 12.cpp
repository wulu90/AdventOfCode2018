#include <fstream>
#include <map>
#include <string>

using namespace std;

void part1() {
    ifstream input("input/input12");
    string line;
    getline(input, line);
    string state = line.substr(15);
    getline(input, line);

    map<string, char> rules;
    while (getline(input, line)) {
        rules.insert({line.substr(0, 5), line.back()});
    }
    size_t dot_start = 0;
    size_t dot_back  = 0;
    for (auto& [pattern, _] : rules) {
        auto p1 = pattern.find('#');
        if (p1 == string::npos) {
            p1 = 5;
        }
        dot_start = max(dot_start, p1);
        auto p2   = pattern.rfind('#');
        dot_back  = max(dot_back, pattern.size() - 1 - p2);
    }

    int curr = 0;

    for (size_t i = 0; i < 20; ++i) {
        auto first_plant = state.find('#');
        auto last_plant  = state.rfind('#');
        string tmp_state;
        if (dot_start > first_plant) {
            tmp_state.append(dot_start - first_plant, '.');
            curr = curr - (dot_start - first_plant);
        }
        tmp_state += state;
        if (dot_back > (state.size() - 1 - last_plant)) {
            tmp_state.append(dot_back - (state.size() - 1 - last_plant), '.');
        }
        string next_state(tmp_state.size(), '.');
        for (size_t j = 2; j < tmp_state.size() - 2; ++j) {
            next_state[j] = rules[tmp_state.substr(j - 2, 5)];
        }
        state = std::move(next_state);
    }
    int sum = 0;
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] == '#') {
            sum += i + curr;
        }
    }

    println("{}", sum);
}

int main() {
    part1();
    return 0;
}
