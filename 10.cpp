#include <fstream>
#include <string>
#include <vector>

using namespace std;

pair<pair<int, int>, pair<int, int>> parse_pos_vel(const string& str) {
    int px, py, vx, vy;
    sscanf(str.data(), "position=<%d, %d> velocity=<%d, %d>", &px, &py, &vx, &vy);
    // println("{},{},{},{}", px, py, vx, vy);
    return {{px, py}, {vx, vy}};
}

pair<double, double> calculateVariance(const vector<pair<int, int>>& pos) {
    double x_mean = 0, y_mean = 0;
    for (const auto& [x, y] : pos) {
        x_mean += x;
        y_mean += y;
    }
    x_mean /= pos.size();
    y_mean /= pos.size();

    double x_var = 0, y_var = 0;
    for (const auto& [x, y] : pos) {
        x_var += (x - x_mean) * (x - x_mean);
        y_var += (y - y_mean) * (y - y_mean);
    }

    x_var /= pos.size();
    y_var /= pos.size();

    return {sqrt(x_var), sqrt(y_var)};
}

void print_pos(const vector<pair<int, int>>& pos) {
    auto x_max = numeric_limits<int>::min();
    auto x_min = numeric_limits<int>::max();
    auto y_max = x_max;
    auto y_min = x_min;

    for (const auto& [x, y] : pos) {
        x_max = max(x_max, x);
        x_min = min(x_min, x);
        y_max = max(y_max, y);
        y_min = min(y_min, y);
    }

    string row(x_max - x_min + 1, ' ');
    vector<string> image(y_max - y_min + 1, row);

    for (const auto& [x, y] : pos) {
        image[y_max - y][x - x_min] = '#';
    }

    for (const auto& str : image) {
        println("{}", str);
    }
}

void part1() {
    ifstream input("input/input10");
    vector<pair<int, int>> pos_vec;
    vector<pair<int, int>> vel_vec;
    for (string line; getline(input, line);) {
        auto&& [pos, vel] = parse_pos_vel(line);
        pos_vec.push_back(pos);
        vel_vec.push_back(vel);
    }

    while (true) {
        for (size_t i = 0; i < pos_vec.size(); ++i) {
            pos_vec[i].first += vel_vec[i].first;
            pos_vec[i].second += vel_vec[i].second;
        }

        auto var = calculateVariance(pos_vec);

        if (var.first < 19 && var.second < 19) {
            print_pos(pos_vec);
            break;
        }
        /*
        if (var.first < 20 && var.second < 20) {
            for (size_t j = 0; j < 100; ++j) {
                for (size_t i = 0; i < pos_vec.size(); ++i) {
                    pos_vec[i].first += vel_vec[i].first;
                    pos_vec[i].second += vel_vec[i].second;
                }
                print_pos(pos_vec);
                println();
            }
            break;
        }
        */
    }
}

int main() {
    part1();
    return 0;
}
