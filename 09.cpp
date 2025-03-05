#include <list>
#include <print>
#include <vector>

using namespace std;

void part1() {
    int player_num  = 476;
    int last_marble = 71657;

    list marble_list{0};
    vector<int> score_vec(player_num, 0);

    int marble      = 1;
    int player_turn = 0;
    auto curr       = marble_list.begin();
    auto head       = marble_list.begin();
    auto tail       = marble_list.end();
    while (marble <= last_marble) {
        if (marble % 23 == 0) {
            score_vec[player_turn % player_num] += marble;
            int counter_clockwise = 7;

            while (counter_clockwise > 0) {
                if (curr == head) {
                    curr = next(tail, -1);
                } else {
                    --curr;
                }
                --counter_clockwise;
            }
            score_vec[player_turn % player_num] += *curr;
            auto tmp = curr;
            ++curr;
            if (curr == tail) {
                curr = head;
            }
            marble_list.erase(tmp);
        } else {
            ++curr;
            if (curr == tail) {
                curr = head;
            }
            ++curr;
            curr = marble_list.insert(curr, marble);
        }
        ++marble;
        ++player_turn;
    }

    println("{}", *max_element(score_vec.begin(), score_vec.end()));
}

int main() {
    part1();
    return 0;
}
