#include <fstream>
#include <numeric>
#include <print>
#include <vector>

using namespace std;

struct node {
    node* parent;
    vector<node*> children;
    vector<int> metadata;
};

node* parse_tree(const vector<int>& license, node* parent, size_t& index) {
    node* n             = new node;
    n->parent           = parent;
    size_t children_num = license[index];
    size_t metadata_num = license[index + 1];
    index += 2;
    for (size_t i = 0; i < children_num; ++i) {
        size_t child_len = 0;
        n->children.push_back(parse_tree(license, n, index));
    }

    for (size_t i = 0; i < metadata_num; ++i) {
        n->metadata.push_back(license[index++]);
    }
    return n;
}

int meta_sum(node* n) {
    int sum = accumulate(n->metadata.begin(), n->metadata.end(), 0, [](auto lhs, auto& rhs) { return lhs + rhs; });
    for (auto child : n->children) {
        sum += meta_sum(child);
    }
    return sum;
}

void part1() {
    ifstream input("input/input08");
    vector<int> license;
    for (int n; input >> n;) {
        license.push_back(n);
    }
    size_t index = 0;
    node* root   = parse_tree(license, nullptr, index);

    println("{}", meta_sum(root));
}

int main() {
    part1();
    return 0;
}
