#include <algorithm>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

using namespace std;

void part1() {
    vector<array<int, 4>> regs_vec;
    vector<array<int, 4>> samp_vec;
    vector<array<int, 4>> test_vec;

    ifstream input("input/input16");
    for (string line; getline(input, line) && line.starts_with("Before");) {
        int a, b, c, d;
        sscanf(line.data(), "Before: [%d,%d,%d,%d]", &a, &b, &c, &d);
        regs_vec.push_back({a, b, c, d});

        getline(input, line);
        sscanf(line.data(), "%d %d %d %d", &a, &b, &c, &d);
        samp_vec.push_back({a, b, c, d});

        getline(input, line);
        sscanf(line.data(), "After:  [%d,%d,%d,%d]", &a, &b, &c, &d);
        regs_vec.push_back({a, b, c, d});

        getline(input, line);    // skip blank line
    }

    for (int a, b, c, d; input >> a && input;) {
        input >> b;
        input >> c;
        input >> d;
        test_vec.push_back({a, b, c, d});
    }

    vector<function<void(int, int, int, array<int, 4>&)>> ins_vec{
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] + regs[b]; },            // addr
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] + b; },                  // addi
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] * regs[b]; },            // mulr
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] * b; },                  // muli
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] & regs[b]; },            // banr
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] & b; },                  // bani
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] | regs[b]; },            // borr
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] | b; },                  // bori
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a]; },                      // setr
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = a; },                            // seti
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = a > regs[b] ? 1 : 0; },          // gtir
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] > b ? 1 : 0; },          // gtri
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] > regs[b] ? 1 : 0; },    // gtrr
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = a == regs[b] ? 1 : 0; },         // eqir
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] == b ? 1 : 0; },         // eqri
        [](int a, int b, int c, array<int, 4>& regs) { regs[c] = regs[a] == regs[b] ? 1 : 0; }    // eqrr
    };

    int oplike3 = 0;
    for (size_t i = 0; i < samp_vec.size(); ++i) {
        auto before = regs_vec[i * 2];
        auto after  = regs_vec[i * 2 + 1];
        auto samp   = samp_vec[i];
        auto oplike = count_if(ins_vec.begin(), ins_vec.end(), [&before, &after, &samp](auto& func) {
            auto tmp = before;
            func(samp[1], samp[2], samp[3], tmp);
            return tmp == after;
        });
        if (oplike >= 3) {
            ++oplike3;
        }
    }

    println("{}", oplike3);
}

int main() {
    part1();
    return 0;
}
