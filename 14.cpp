#include <algorithm>
#include <print>
#include <ranges>
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

void part2() {
    const size_t input = 652601;

    vector<uint8_t> score_i;

    for (size_t n = input; n != 0; n /= 10) {
        score_i.push_back(static_cast<uint8_t>(n % 10));
    }

    vector<uint8_t> scores_vec{3, 7};
    size_t elve_1 = 0;
    size_t elve_2 = 1;

    // may be push back one or two
    while (!(ranges::starts_with(scores_vec | views::reverse, score_i) ||
             ranges::starts_with(scores_vec | views::reverse | views::drop(1), score_i))) {
        auto sum = scores_vec[elve_1] + scores_vec[elve_2];
        if (sum > 9) {
            scores_vec.push_back(1u);
        }
        scores_vec.push_back(sum % 10);

        elve_1 = (elve_1 + 1 + scores_vec[elve_1]) % scores_vec.size();
        elve_2 = (elve_2 + 1 + scores_vec[elve_2]) % scores_vec.size();
    }
    if (ranges::starts_with(scores_vec | views::reverse, score_i)) {
        println("{}", scores_vec.size() - score_i.size());
    } else {
        println("{}", scores_vec.size() - score_i.size() - 1);
    }
}

int main() {
    part1();
    part2();
    return 0;
}
