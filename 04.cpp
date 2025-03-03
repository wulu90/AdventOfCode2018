#include <algorithm>
#include <charconv>
#include <fstream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

struct record {
    int year;
    int month;
    int day_m;
    int hour_24;
    int minute;
    string guard_status;

    record(const string& str) {
        sscanf(str.data(), "[%d-%d-%d %d:%d]", &year, &month, &day_m, &hour_24, &minute);
        guard_status = str.substr(19);
    }

    friend bool operator<(const record& lhs, const record& rhs) {
        return tie(lhs.year, lhs.month, lhs.day_m, lhs.hour_24, lhs.minute) < tie(rhs.year, rhs.month, rhs.day_m, rhs.hour_24, rhs.minute);
    }
};

void part1_2() {
    ifstream input("input/input04");
    vector<record> record_vec;
    for (string line; getline(input, line);) {
        record_vec.emplace_back(line);
    }
    sort(record_vec.begin(), record_vec.end());

    map<int, vector<pair<int, int>>> guard_sleep_periods;

    int guard_no;
    int sleep_start;
    int sleep_end;
    for (auto& rec : record_vec) {
        if (rec.guard_status.starts_with("Guard")) {
            auto p = rec.guard_status.find(' ', 6);
            from_chars(rec.guard_status.data() + 7, rec.guard_status.data() + p, guard_no);
        } else if (rec.guard_status == "falls asleep") {
            sleep_start = rec.minute;
        } else if (rec.guard_status == "wakes up") {
            sleep_end = rec.minute;
            guard_sleep_periods[guard_no].push_back({sleep_start, sleep_end});
        }
    }

    auto sleep_most = max_element(guard_sleep_periods.begin(), guard_sleep_periods.end(), [](auto& p1, auto& p2) {
        return accumulate(p1.second.begin(), p1.second.end(), 0, [](auto t1, auto t2) { return t1 + t2.second - t2.first; }) <
               accumulate(p2.second.begin(), p2.second.end(), 0, [](auto t1, auto t2) { return t1 + t2.second - t2.first; });
    });

    array<int, 60> sleep_minutes;
    sleep_minutes.fill(0);
    for (auto [s, e] : sleep_most->second) {
        for (int i = s; i < e; ++i) {
            ++sleep_minutes[i];
        }
    }

    println("{}", sleep_most->first * (max_element(sleep_minutes.begin(), sleep_minutes.end()) - sleep_minutes.begin()));

    map<int, array<int, 60>> guard_minutes_sleep_times;
    for (auto [id, vec] : guard_sleep_periods) {
        array<int, 60> arr;
        arr.fill(0);
        for (auto [s, e] : vec) {
            for (int i = s; i < e; ++i) {
                ++arr[i];
            }
        }
        guard_minutes_sleep_times.insert({id, arr});
    }

    auto minutes_most = max_element(guard_minutes_sleep_times.begin(), guard_minutes_sleep_times.end(), [](auto& g1, auto& g2) {
        return *max_element(g1.second.begin(), g1.second.end()) < *max_element(g2.second.begin(), g2.second.end());
    });

    println("{}",
            minutes_most->first * (max_element(minutes_most->second.begin(), minutes_most->second.end()) - minutes_most->second.begin()));
}

int main() {
    part1_2();
    return 0;
}
