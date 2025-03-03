#include <fstream>
#include <print>
#include <set>
#include <vector>

using namespace std;

void part1() {
    ifstream input("input/input01");
    int fre = 0;
    for (int num; input >> num;) {
        fre += num;
    }
    println("{}", fre);
}

void part2() {
    ifstream input("input/input01");
    int fre = 0;
    set<int> fre_set{fre};
    vector<int> change_vec;
    for (int num; input >> num;) {
        change_vec.push_back(num);
    }

    bool twice = false;
    while (true) {
        for (auto n : change_vec) {
            fre += n;
            if (fre_set.contains(fre)) {
                println("{}", fre);
                twice = true;
                break;
            } else {
                fre_set.insert(fre);
            }
        }
        if (twice) {
            break;
        }
    }
}

int main() {
    part1();
    part2();
    return 0;
}
