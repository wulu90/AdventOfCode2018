#include <algorithm>
#include <fstream>
#include <functional>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

void part1_2() {
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

    map<int, set<size_t>> samp_options;
    for (size_t i = 0; i < samp_vec.size(); ++i) {
        auto before = regs_vec[i * 2];
        auto after  = regs_vec[i * 2 + 1];
        auto samp   = samp_vec[i];

        for (size_t j = 0; j < ins_vec.size(); ++j) {
            auto tmp = before;
            ins_vec[j](samp[1], samp[2], samp[3], tmp);
            if (tmp == after) {
                samp_options[samp[0]].insert(j);
            }
        }
    }

    while (!all_of(samp_options.begin(), samp_options.end(), [](auto& sa_opts) {
        auto& [sa, opts] = sa_opts;
        return opts.size() == 1;
    })) {
        set<size_t> inx;
        for_each(samp_options.begin(), samp_options.end(), [&inx](auto& sa_opts) {
            auto& [sa, opts] = sa_opts;
            if (opts.size() == 1) {
                inx.insert(*opts.begin());
            }
        });

        for_each(samp_options.begin(), samp_options.end(), [&inx](auto& sa_opts) {
            auto& [sa, opts] = sa_opts;
            if (opts.size() > 1) {
                set<size_t> tmp;
                set_difference(opts.begin(), opts.end(), inx.begin(), inx.end(), inserter(tmp, tmp.begin()));
                opts = tmp;
            }
        });
    }

    map<int, size_t> samp_ins;
    for (auto& [op, opts] : samp_options) {
        samp_ins.insert({op, *opts.begin()});
    }
    // println("{}", samp_ins);

    array<int, 4> oregs{0, 0, 0, 0};

    for (auto [a, b, c, d] : test_vec) {
        ins_vec[samp_ins[a]](b, c, d, oregs);
    }

    println("{}", oregs[0]);
}

int main() {
    part1_2();
    return 0;
}
