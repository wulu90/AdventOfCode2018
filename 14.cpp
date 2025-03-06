#include <print>
#include <vector>

using namespace std;

void part1() {
    const size_t input = 652601;
    vector<uint8_t> scores_vec{3, 7};
    size_t elve_1 = 0;
    size_t elve_2 = 1;

    for (size_t i = 0; i < input + 10; ++i) {
        auto sum = scores_vec[elve_1] + scores_vec[elve_2];
        if (sum > 9) {
            scores_vec.push_back(1);
        }
        scores_vec.push_back(sum % 10);

        elve_1 = (elve_1 + 1 + scores_vec[elve_1]) % scores_vec.size();
        elve_2 = (elve_2 + 1 + scores_vec[elve_2]) % scores_vec.size();
    }

    for (size_t i = input; i < input + 10; ++i) {
        print("{}", scores_vec[i]);
    }
    println();
}

int main() {
    part1();
    return 0;
}
