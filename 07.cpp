#include <algorithm>
#include <fstream>
#include <map>
#include <print>
#include <ranges>
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

struct worker {
    char le;
    bool idle{true};
    int time;
};

void part2() {
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
    array<worker, 5> waitlist;

    for (auto it = waitlist.begin(); it != waitlist.end() && !opts.empty(); ++it) {
        auto c   = *opts.begin();
        it->le   = c;
        it->idle = false;
        it->time = c - 'A' + 1 + 60;
        opts.erase(c);
    }

    string order;
    int time_all = 0;
    while (order.size() < ins_map.size()) {
        set<char> waiting_letters;
        auto working_workers = waitlist | views::filter([](auto& wo) { return !wo.idle; });
        auto min_time_it =
            min_element(working_workers.begin(), working_workers.end(), [](auto& t1, auto& t2) { return t1.time < t2.time; });
        auto min_time = min_time_it->time;
        time_all += min_time;
        ranges::for_each(working_workers, [min_time, &order, &waiting_letters](auto& wo) {
            wo.time -= min_time;
            if (wo.time == 0) {
                wo.idle = true;
                order.push_back(wo.le);
            } else {
                waiting_letters.insert(wo.le);
            }
        });

        set<char> opt_tmp;
        set<char> done{order.begin(), order.end()};

        for (auto c : order) {
            for (auto cn : ins_map[c].next) {
                if (!waiting_letters.contains(cn) && !done.contains(cn) &&
                    all_of(ins_map[cn].prev.begin(), ins_map[cn].prev.end(), [&done](auto it) { return done.contains(it); })) {
                    opt_tmp.insert(cn);
                }
            }
        }

        for (auto c : opt_tmp) {
            opts.insert(c);
        }

        auto idle_workers = waitlist | views::filter([](auto& wo) { return wo.idle; });

        for (auto w_it = idle_workers.begin(); w_it != idle_workers.end() && !opts.empty(); ++w_it) {
            auto c     = *opts.begin();
            w_it->le   = c;
            w_it->idle = false;
            w_it->time = c - 'A' + 1 + 60;
            opts.erase(c);
        }
    }

    println("{}", time_all);
}

int main() {
    part1();
    part2();
    return 0;
}
