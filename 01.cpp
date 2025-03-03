#include <fstream>
#include <print>

using namespace std;

void part1() {
    ifstream input("input/input01");
    int res = 0;
    for (int num; input >> num;) {
        res += num;
    }
    println("{}", res);
}

int main() {
    part1();
    return 0;
}
