#include <algorithm>
#include <fstream>
#include <map>
#include <set>
#include <string>

using namespace std;

struct step {
    string prev;
    string next;
};

void part1() {
    ifstream input("input/input07");
    map<char, step> ins_map;
    for (string line; getline(input, line);) {
        ins_map[line[5]].next.push_back(line[36]);
        ins_map[line[36]].prev.push_back(line[5]);
    }

    set<char> opts;
    for (auto& [c, step] : ins_map) {
        if (step.prev.empty()) {
            opts.insert(c);
        }
    }

    string order;

    while (order.size() < ins_map.size()) {
        set<char> opt_tmp;
        set<char> done{order.begin(), order.end()};

        for (auto c : opts) {
            for (auto cn : ins_map[c].next) {
                if (all_of(ins_map[cn].prev.begin(), ins_map[cn].prev.end(), [&done](auto it) { return done.contains(it); })) {
                    opt_tmp.insert(cn);
                }
            }
        }

        for (auto c : opt_tmp) {
            opts.insert(c);
        }

        for (auto c : opts) {
            if (!order.contains(c)) {
                order.push_back(c);
                break;
            }
        }
    }

    println("{}", order);
}

int main() {
    part1();
    return 0;
}
