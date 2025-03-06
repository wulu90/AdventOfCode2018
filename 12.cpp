#include <cstdint>
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

void part2() {
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

    map<string, pair<int64_t, int64_t>> state_map;    // string state, first # index, generation times;
    state_map.insert({state, {0, 0}});
    int64_t first_plant_index = 0;
    for (size_t i = 0; i < 50000000000; ++i) {
        auto first_plant_pos = state.find('#');
        auto last_plant_pos  = state.rfind('#');
        string tmp_state;
        int dot_added = 0;
        if (dot_start > first_plant_pos) {
            tmp_state.append(dot_start - first_plant_pos, '.');
            dot_added = dot_start - first_plant_pos;
        }
        tmp_state += state;
        if (dot_back > (state.size() - 1 - last_plant_pos)) {
            tmp_state.append(dot_back - (state.size() - 1 - last_plant_pos), '.');
        }
        string next_state(tmp_state.size(), '.');
        for (size_t j = 2; j < tmp_state.size() - 2; ++j) {
            next_state[j] = rules[tmp_state.substr(j - 2, 5)];
        }

        first_plant_pos = next_state.find('#');
        last_plant_pos  = next_state.rfind('#');
        next_state      = next_state.substr(first_plant_pos, last_plant_pos - first_plant_pos + 1);
        if (state_map.contains(next_state)) {
            println("{},{},{}", state_map[next_state], first_plant_index - dot_added + first_plant_pos, i);
            auto& prev        = state_map[next_state];
            first_plant_index = first_plant_index - dot_added + first_plant_pos;

            first_plant_index += ((50000000000 - 1 - i) / (i - prev.second)) * (first_plant_index - prev.first);
            int64_t sum = 0;
            for (int j = 0; j < next_state.size(); ++j) {
                if (state[j] == '#') {
                    sum += j + first_plant_index;
                }
            }
            println("{}", sum);

            break;
        } else {
            first_plant_index = first_plant_index - dot_added + first_plant_pos;
            state_map.insert({next_state, {first_plant_index, i}});
            state = next_state;
        }
    }
}

int main() {
    part1();
    part2();
    return 0;
}
